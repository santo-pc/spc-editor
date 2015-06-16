#pragma once

#include <string>
#include <GL\glew.h>

class MyTexture
{
	public:
		MyTexture(const std::string& filename);
		void Bind();
		~MyTexture();
	private:
		GLuint m_texture;


};

