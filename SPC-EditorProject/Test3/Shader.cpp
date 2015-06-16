#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

//static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
//static std::string LoadShader(const std::string& fileName);
//static GLuint CreateShader(const std::string& text, GLenum type);
//
//Shader::Shader(const std::string& fileName)
//{
//	m_program = glCreateProgram();
//	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
//	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
//	for (unsigned int i = 0; i < NUM_SHADERS; i++)
//		glAttachShader(m_program, m_shaders[i]);
//
//	glBindAttribLocation(m_program, 0, "position");
//	glBindAttribLocation(m_program, 1, "texCoord");
//	glBindAttribLocation(m_program, 2, "normal");
//	glLinkProgram(m_program);
//	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader linking failed: ");
//	glValidateProgram(m_program);
//	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Invalid shader program ");
//	m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
//	m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
//	m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
//
//	std::cout << "Shader 6 " << std::endl;
//}
//
//Shader::~Shader()
//{
//	for (unsigned int i = 0; i < NUM_SHADERS; i++)
//	{
//		glDetachShader(m_program, m_shaders[i]);
//		glDeleteShader(m_shaders[i]);
//	}
//
//	glDeleteProgram(m_program);
//}
//
//void Shader::Bind()
//{
//	glUseProgram(m_program);
//}
//
//void Shader::Update(const Transform& transform, const Camera& camera)
//{
//	Transform transform2;
//	Camera camera2(glm::vec3(0.0f, 0.0f, -10.0f), 90.0f, (float)400 / (float)300, 0.1f, 1500.0f);
//	
//	
//	glm::mat4 MVP = transform2.GetMVP(camera2);
//	glm::mat4 Normal = transform2.GetModel();
//
//	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
//	glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
//	glUniform3f(m_uniforms[2], -0.4f, 0.3f, 1.0f);
//}
//
//static GLuint CreateShader(const std::string& text, GLenum type)
//{
//	GLuint shader = glCreateShader(type);
//
//	if (shader == 0)
//		std::cerr << "Error compiling shader type " << type << std::endl;
//
//	const GLchar* p[1];
//	p[0] = text.c_str();
//	GLint lengths[1];
//	lengths[0] = text.length();
//
//	glShaderSource(shader,1, p, lengths);
//	glCompileShader(shader);
//
//	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
//
//	return shader;
//}
//
//static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
//{
//	GLint success = 0;
//	GLchar error[1024] = { 0 };
//
//	if (isProgram)
//		glGetProgramiv(shader, flag, &success);
//	else
//		glGetShaderiv(shader, flag, &success);
//
//	if (success == GL_FALSE)
//	{
//		if (isProgram)
//			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
//		else
//			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
//
//		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
//	}
//}
//
//
//static std::string LoadShader(const std::string& fileName)
//{
//	std::ifstream file;
//	file.open((fileName).c_str());
//
//	std::string output;
//	std::string line;
//
//	if (file.is_open())
//	{
//		while (file.good())
//		{
//			getline(file, line);
//			output.append(line + "\n");
//		}
//	}
//	else
//	{
//		std::cerr << "Unable to load shader: " << fileName << std::endl;
//	}
//
//	return output;
//}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum type);

Shader::Shader(){}
Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "VertexPosition");
	glBindAttribLocation(m_program, 1, "VertexTexCoord");
	glBindAttribLocation(m_program, 2, "VertexNormal");
	glBindAttribLocation(m_program, 4, "VertexTangent");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Invalid shader program ");
	

	RegisterUniform("ModelViewMatrix");
	RegisterUniform("NormalMatrix");
	RegisterUniform("ProjectionMatrix");
	RegisterUniform("MVP");
	RegisterUniform("ColorTex");
	RegisterUniform("NormalMapTex");
	RegisterUniform("SpecularMapTex");
	RegisterUniform("Material.Ka");
	RegisterUniform("Material.Ks");
	RegisterUniform("Material.Shininess");
	RegisterUniform("Model");
	RegisterUniform("MAX_NUM_LIGHTS");
	RegisterUniform("AtteConstantTest");
	RegisterUniform("AtteLinearTest");
	RegisterUniform("AtteExpTest");
	RegisterUniform("LightDirStatic");

	std::cout << "Shading Program " << m_program << " Created: " << m_uniformLocations.size() << " uniforms" << std::endl;
	


}

void Shader::RegisterUniform(const char *name)
{
	int uniform = glGetUniformLocation(m_program, name);
	m_uniforms.push_back(uniform);
	m_uniformLocations.insert(std::pair<std::string, int>(name, uniform));
	uniformIndex++;
}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}


void Shader::Update(const Transform& transform, const Camera& camera)
{
	Transform transform2;
	//Camera camera2(glm::vec3(0.0f, 0.0f, -10.0f), 90.0f, (float)400 / (float)300, 0.1f, 1500.0f);
	
	
	glm::mat4 MVP = transform2.GetMVP(camera);
	glm::mat4 ModelView = camera.GetView() * transform2.GetModel();
	glm::mat4 Normal = transform2.GetModel();
	glm::mat4 P = camera.GetProjection();

	SetUniform("MVP", MVP);
	SetUniform("ModelViewMatrix", ModelView);
	SetUniform("NormalMatrix", MVP);	
	SetUniform("ProjectionMatrix", MVP);
	SetUniform("LightDirStatic", glm::vec3(-0.4f, 0.3f, 1.0f));
}

GLuint Shader::GetProgramHandler()
{
	return m_program;
}

void Shader::SetUniform(const char *name, float x, float y, float z)
{
	GLint loc = GetUniformLocation(name);
	glUniform3f(loc, x, y, z);
}

void Shader::SetUniform(const char *name, const glm::vec3 & v)
{
	this->SetUniform(name, v.x, v.y, v.z);
}

void Shader::SetUniform(const char *name, const glm::vec4 & v)
{
	GLint loc = GetUniformLocation(name);
	glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void Shader::SetUniform(const char *name, const glm::vec2 & v)
{
	GLint loc = GetUniformLocation(name);
	glUniform2f(loc, v.x, v.y);
}

void Shader::SetUniform(const char *name, const glm::mat4 & m)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniform(const char *name, const glm::mat3 & m)
{
	GLint loc = GetUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniform(const char *name, float val)
{
	GLint loc = GetUniformLocation(name);
	//if (loc >=0)
	glUniform1f(loc, val);
	//fprintf(stderr, "Uniform variable %s not found!\n", name);
}

void Shader::SetUniform(const char *name, int val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1i(loc, val);
}

void Shader::SetUniform(const char *name, GLuint val)
{
	GLint loc = GetUniformLocation(name);
	glUniform1ui(loc, val);
}

void Shader::SetUniform(const char *name, bool val)
{
	int loc = GetUniformLocation(name);
	glUniform1i(loc, val);
}


int Shader::GetUniformLocation(const char * name)
{
	std::map<std::string, int>::iterator pos;
	pos = m_uniformLocations.find(name);

	if (pos == m_uniformLocations.end())
	{
		m_uniformLocations[name] = glGetUniformLocation(m_program, name);
	}

	return m_uniformLocations[name];
}

static GLuint CreateShader(const std::string& text, GLenum type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}



GlobalContainer * GlobalContainer::Instance()
{
	static GlobalContainer instance;

	return &instance;
}

GlobalContainer::GlobalContainer()
{
}
GlobalContainer::~GlobalContainer()
{
}
