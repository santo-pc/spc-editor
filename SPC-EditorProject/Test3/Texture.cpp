#include "stb_image.h"
#include <cassert>
#include <iostream>
#include "Texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
	m_textureTarget = TextureTarget;
	m_fileName      = FileName;
}


bool Texture::Load()
{
	int width, height, numComponents;
	int num_mipmaps = 2;
	unsigned char* imageData = stbi_load((m_fileName).c_str(), &width, &height, &numComponents, 4);


	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << m_fileName << std::endl;

	printf("\nOpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	std::cout <<"Cargando textura "<<  m_fileName << std::endl;


	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 6);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);	
	glGenerateMipmap(GL_TEXTURE_2D);  //Generate num_mipmaps number of mipmaps here.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	


	stbi_image_free(imageData);
	return true;
}

void Texture::Bind(int unit)
{
	glActiveTexture(unit);
	glBindTexture(m_textureTarget, m_textureObj);
}
