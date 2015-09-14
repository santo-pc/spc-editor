/*

	Copyright 2011 Etay Meiri

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include <GL/glew.h>

const int DIFFUSE_TEXTURE_UNIT_INDEX = 0;
const int DIFFUSE_TEXTURE_UNIT = GL_TEXTURE0;

const int NORMAL_TEXTURE_UNIT_INDEX = 1;
const int NORMAL_TEXTURE_UNIT = GL_TEXTURE1;

const int SPECULAR_TEXTURE_UNIT_INDEX = 2;
const int SPECULAR_TEXTURE_UNIT = GL_TEXTURE2;

const int RANDOM_TEXTURE_UNIT_INDEX = 3;
const int RANDOM_TEXTURE_UNIT = GL_TEXTURE3;


class Texture
{
	public:
		Texture(GLenum TextureTarget, const std::string& FileName);

		bool Load();
		void Bind(int unit);
		void Delete();

	private:
		std::string m_fileName;
		GLenum m_textureTarget;
		GLuint m_textureObj;		
};


#endif	/* TEXTURE_H */

