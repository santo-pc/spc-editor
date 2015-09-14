#include "TextureManager.h"
#include "Shader.h"
#include "StringsAndDefines.h"

TextureManager * TextureManager::Instance()
{
	static TextureManager instance;

	return &instance;
}

TextureManager::TextureManager()
{
	SetStandarMode();
}


TextureManager::~TextureManager()
{
}

void TextureManager::SetStandarMode()
{

	textureVector.clear();
	AddTexture(0, 0, STANDAR_TEXTURE_PATH, UNIFORM_NAME_TEXTURE_COLOR);
	AddTexture(1, 1, STANDAR_TEXTURE_NORMAL_PATH, UNIFORM_NAME_TEXTURE_NORMAL);
	AddTexture(2, 2, STANDAR_TEXTURE_SPECULAR_PATH, UNIFORM_NAME_TEXTURE_SPECULAR);
}

bool TextureManager::AddTexture(int unitIndex, int unit, string path, string memberName)
{
	bool result = true;
	TextureInfo info;
	info.unit = unit;
	info.unitIndex = unitIndex;
	info.memberName = memberName;
	info.path = path;
	info.uniformName = memberName;	
	info.texture = new Texture(GL_TEXTURE_2D, path);

	if (info.texture->Load())
		result = true;
	else
		result =  false;
	
	GLOBAL_CONTAIER->GlobalShader->RegisterUniform(info.memberName.c_str()); // Lo registro el uniform
	
	textureVector.push_back(info);
	
	return result;
}

void TextureManager::DrawTextures1()
{
	int count = 0;
	vector<TextureInfo>::const_iterator it;
	for (it = textureVector.begin(); it != textureVector.end(); ++it)
	{
		TextureInfo info = (*it);

		if (info.texture)
		{
			//cout << "Pintando Textura 1" << count << endl; count++;
			GLOBAL_CONTAIER->GlobalShader->SetUniform(info.uniformName.c_str(), info.unitIndex);
			//cout << "GLInt = " << GL_TEXTURE0 << " unit = " << info.unit << " IGUAL "<< GL_TEXTURE0 + info.unit << endl;
			//info.texture->Bind(GL_TEXTURE0 + info.unit);
		}

	}

}

void TextureManager::DrawTextures2()
{
	int count = 0;
	vector<TextureInfo>::const_iterator it;
	for (it = textureVector.begin(); it != textureVector.end(); ++it)
	{
		TextureInfo info = (*it);

		if (info.texture)
		{
			//cout << "Pintando Textura 2" << count << endl; count++;
			//GLOBAL_CONTAIER->GlobalShader->SetUniform(info.uniformName.c_str(), info.unitIndex);
			//cout << "GLInt = " << GL_TEXTURE0 << " unit = " << info.unit << " IGUAL " << GL_TEXTURE0 + info.unit << endl;
			info.texture->Bind(GL_TEXTURE0 + info.unit);
		}

	}

}


void TextureManager::FreeTextures()
{
	cout << "Liberando texturas..." << endl;
	vector<TextureInfo>::const_iterator it;
	for (it = textureVector.begin(); it != textureVector.end(); ++it)
	{
		if ((*it).texture)
		{
			(*it).texture->Delete();

			delete (*it).texture;
		}

		//(*it).texture = NULL;
	}

	textureVector.clear();
	cout << "Texturas liberas OK"<< endl;
}