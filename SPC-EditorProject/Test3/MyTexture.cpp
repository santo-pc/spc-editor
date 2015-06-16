#include "MyTexture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

MyTexture::MyTexture(const std::string& filename)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load((filename).c_str(), &width, &height, &numComponents, 4);


	if (imageData == NULL)
		std::cerr << "Texture loading failed for texture: "<< filename << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	
	
	// gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,width, height, 	GL_RGBA, GL_UNSIGNED_BYTE,imageData);
	
	
	stbi_image_free(imageData);

	std::cout <<std::endl<< "GL VERSION " <<  GL_VERSION << std::endl;
}



MyTexture::~MyTexture()
{
	glDeleteTextures(1, &m_texture);
}


void MyTexture::Bind()
{
	
	//assert(unit >= 0 && unit <= 31);
	//glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}