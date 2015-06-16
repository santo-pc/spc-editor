#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h> 
#include <assimp\scene.h>


#include "Texture.h"

struct MeshMaterial
{
	glm::vec3 Ka;
	glm::vec3 Ks;
	float Shininess;
	Texture * diffuseMap;
	Texture * normalMap;
	Texture * specularMap;
	MeshMaterial()
	{
		Ka = glm::vec3(0.3f, 0.3f, 0.3f);
		Ks = glm::vec3(0.3f, 0.3f, 0.3f);
		Shininess = 20;
		diffuseMap = NULL;
		normalMap = NULL;
		specularMap = NULL;
	}
};

struct Vertex
{
	glm::vec3 m_pos;
	glm::vec2 m_tex;
	glm::vec3 m_normal;
	glm::vec4 m_tangent;

	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal, glm::vec4 &tangent)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
		m_tangent = tangent;
	}
};


class Mesh
{
	public:
		Mesh();

		~Mesh();

		bool LoadMesh(const std::string& Filename);

		void Render();

	private:
		bool InitFromScene(const aiScene* pScene, const std::string& Filename);
		void InitMesh(unsigned int Index, const aiMesh* paiMesh);
		bool InitMaterials(const aiScene* pScene, const std::string& Filename);
		void Clear();
		#define INVALID_MATERIAL 0xFFFFFFFF

		struct MeshEntry 
		{
				MeshEntry();

				~MeshEntry();

				void Init(const std::vector<Vertex>& Vertices,
					const std::vector<unsigned int>& Indices);

				GLuint VB;
				GLuint IB;
				unsigned int NumIndices;
				unsigned int MaterialIndex;
		};

		std::vector<MeshEntry> m_Entries;
		std::vector<Texture*> m_Textures;
		std::vector<MeshMaterial*> m_Materiales;
};

