#include "Mesh.h"
#include <vector>
#include <iostream>
#include "Shader.h"

#include <assert.h>

#include "mesh.h"

Mesh::MeshEntry::MeshEntry()
{
	VB = 0;
	IB = 0;
	NumIndices = 0;
	MaterialIndex = INVALID_MATERIAL;
};

Mesh::MeshEntry::~MeshEntry()
{
	if (VB != 0)
	{
		glDeleteBuffers(1, &VB);
	}

	if (IB != 0)
	{
		glDeleteBuffers(1, &IB);
	}
}


void Mesh::MeshEntry::Init(const std::vector<Vertex>& Vertices,	const std::vector<unsigned int>& Indices)
{
	NumIndices = Indices.size();
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	Clear();
}

void Mesh::Clear()
{
	for (unsigned int i = 0; i < m_Textures.size(); i++) {
		// SAFE_DELETE(m_Textures[i]);
	}
}

bool Mesh::LoadMesh(const std::string& Filename)
{
	std::cout << "Loading Mesh" << std::endl;
	// Release the previously loaded mesh (if it exists)
	Clear();

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace);

	if (pScene) 
	{
		Ret = InitFromScene(pScene, Filename);
	}
	else
	{
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
	}

	return Ret;
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);
	m_Materiales.resize(pScene->mNumMaterials);
	for (unsigned int i = 0; i < m_Materiales.size(); i++)  // initialize
		m_Materiales[i] = new MeshMaterial();


	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_Entries.size(); i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];

		InitMesh(i, paiMesh);
	}


	// init materials	
	return InitMaterials(pScene, Filename);
}



void Mesh::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
	{
		float handedness = 1;
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D* pTangents = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mTangents[i]) : &Zero3D;
		const aiVector3D* pBitangents = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mBitangents[i]) : &Zero3D;


		glm::vec3 p(pPos->x, pPos->y, pPos->z);
		glm::vec2 uv(pTexCoord->x, pTexCoord->y);
		glm::vec3 n(pNormal->x, pNormal->y, pNormal->z);
		glm::vec3 t(pTangents->x, pTangents->y, pTangents->z);
		glm::vec3 b(pBitangents->x, pBitangents->y, pBitangents->z);

		glm::mat3 TBN = glm::mat3(t.x, b.x, n.x,
			t.y, b.y, n.y,
			t.z, b.z, n.z);

		handedness = glm::determinant(TBN);
		handedness >= 0 ? handedness = 1 : handedness = -1;

		Vertex v(p, uv, n, glm::vec4(t, handedness));
		Vertices.push_back(v);

		
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	m_Entries[Index].Init(Vertices, Indices);
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	// Extract the directory part from the file name
	std::cout << "InitMaterials 1" << std::endl;
	
	std::string::size_type SlashIndex = Filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos)
	{
		Dir = ".";
	}
	else if (SlashIndex == 0)
	{
		Dir = "/";
	}
	else
	{
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;
	std::cout << "InitMaterials 2" << std::endl;
	// Initialize the materials
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
	{

		//cout << "Material N = " << i << endl;
		std::cout << "InitMaterials 2.5" << std::endl;
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		m_Textures[i] = NULL;
		std::cout << "Bamm 1" << std::endl;
		int hola = pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0 || pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0 || pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0 || pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0;
		std::cout << "Bamm 2" << std::endl;
		
		
		// Hay mas de una textura del tipo que tenemos controlado, DIFFUSE, HEIGHT-NORMAL
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0 ||
			pMaterial->GetTextureCount(aiTextureType_NORMALS) > 0 ||
			pMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0 ||
			pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
		{
			aiString Path;
			std::cout << "InitMaterials 3" << std::endl;
			// DIFFUSES
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string FullPath = Dir + "/" + Path.data;
				m_Materiales[i]->diffuseMap = new Texture(GL_TEXTURE_2D, FullPath.c_str());
				m_Materiales[i]->diffuseMap->Load();

			}


			// NORMALS
			if (pMaterial->GetTexture(aiTextureType_HEIGHT, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string FullPath = Dir + "/" + Path.data;
				m_Materiales[i]->normalMap = new Texture(GL_TEXTURE_2D, FullPath.c_str());
				m_Materiales[i]->normalMap->Load();
			}

			// SPECULAR 
			if (pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string FullPath = Dir + "/" + Path.data;
				m_Materiales[i]->specularMap = new Texture(GL_TEXTURE_2D, FullPath.c_str());
				m_Materiales[i]->specularMap->Load();
			}



		}

		// Load a default textures for diffuse and normals		
		if (!m_Materiales[i]->diffuseMap || !m_Materiales[i]->normalMap || !m_Materiales[i]->specularMap)
		{
			aiString Path;
			std::cout << "InitMaterials 2.6" << std::endl;
			if (!m_Materiales[i]->diffuseMap)
			{

				//m_Materiales[i]->diffuseMap = new CWTexture(GL_TEXTURE_2D, "../../Resources/Graphics/white.png", DIFFUSE_TEXTURE);
				m_Materiales[i]->diffuseMap = new Texture(GL_TEXTURE_2D, "../../Resources/Graphics/white.png");
				Ret = m_Materiales[i]->diffuseMap->Load();

			}

			if (!m_Materiales[i]->normalMap)
			{
				//m_Materiales[i]->normalMap = new CWTexture(GL_TEXTURE_2D, "../../Resources/Graphics/whiteNormal.png", NORMAL_TEXTURE);
				m_Materiales[i]->normalMap = new Texture(GL_TEXTURE_2D, "../../Resources/Graphics/whiteNormal.png");
				Ret = m_Materiales[i]->normalMap->Load();
			}

			if (!m_Materiales[i]->specularMap)
			{
				//m_Materiales[i]->specularMap = new CWTexture(GL_TEXTURE_2D, "../../Resources/Graphics/whiteNormal.png", SPECULAR_TEXTURE);
				m_Materiales[i]->specularMap = new Texture(GL_TEXTURE_2D, "../../Resources/Graphics/whiteSpecular.png");
				Ret = m_Materiales[i]->specularMap->Load();
			}
		}

		// Obtener los componentes de material de phong
		aiColor3D ambient(0.f, 0.f, 0.f);
		pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		aiColor3D specular(0.f, 0.f, 0.f);
		pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		float shininess;
		pMaterial->Get(AI_MATKEY_SHININESS, shininess);

		m_Materiales[i]->Ka = glm::vec3(ambient.r, ambient.g, ambient.b);
		m_Materiales[i]->Ks = glm::vec3(specular.r, specular.g, specular.b);
		m_Materiales[i]->Shininess = shininess;




	}

	return Ret;
}

void Mesh::Render()
{

	glEnableVertexAttribArray(0);	// VertexPosition
	glEnableVertexAttribArray(1);	// VextexTexCoor
	glEnableVertexAttribArray(2);	// VextexNormal
	glEnableVertexAttribArray(3);	// VextexTangent

	for (unsigned int i = 0; i < m_Entries.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);		// = 3*4
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);		// = 3*4 + 2*4
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)32);		// = 3*4 + 2*4 + 3*4

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);



		const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

		if (MaterialIndex < m_Textures.size())
		{

			GLOBAL_CONTAIER->GlobalShader->SetUniform("Material.Ka", m_Materiales[MaterialIndex]->Ka);
			GLOBAL_CONTAIER->GlobalShader->SetUniform("Material.Ks", m_Materiales[MaterialIndex]->Ks);
			GLOBAL_CONTAIER->GlobalShader->SetUniform("Material.Shininess", m_Materiales[MaterialIndex]->Shininess);
			GLOBAL_CONTAIER->GlobalShader->SetUniform("ColorTex", DIFFUSE_TEXTURE_UNIT_INDEX);
			GLOBAL_CONTAIER->GlobalShader->SetUniform("NormalMapTex", NORMAL_TEXTURE_UNIT_INDEX);
			GLOBAL_CONTAIER->GlobalShader->SetUniform("SpecularMapTex", SPECULAR_TEXTURE_UNIT_INDEX);

			m_Materiales[MaterialIndex]->diffuseMap->Bind(DIFFUSE_TEXTURE_UNIT);
			m_Materiales[MaterialIndex]->normalMap->Bind(NORMAL_TEXTURE_UNIT);
			m_Materiales[MaterialIndex]->specularMap->Bind(SPECULAR_TEXTURE_UNIT);
		}


		glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}