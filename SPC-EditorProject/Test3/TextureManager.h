#pragma once
#include "Texture.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class TextureInfo
{
public:
	string path = "";
	string memberName = "";
	string uniformName = "";
	Texture * texture;
	int unitIndex = 0;
	int unit = 0;
};

#define TEXTURE_MANAGER TextureManager::Instance()

class TextureManager
{
private:
	vector<TextureInfo> textureVector;
	TextureManager();
	~TextureManager();
public:
	static TextureManager * Instance();
	void SetStandarMode();
	bool AddTexture(int unitIndex, int unit, string path, string memberName);
	void DrawTextures1();
	void DrawTextures2();
	void FreeTextures();
	//void DrawTextures();



};

