#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <GL/glew.h>


GLuint Shader::CreateShader(const std::string& text, GLenum type)
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

	succes = CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

bool Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
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

		return false;
	}

	return true;
}


bool Shader::Load(const std::string& fileName, std::string vertex = "", std::string fragment = "")
{
	m_program = glCreateProgram();

	if (vertex == "")
		vertex = LoadShader(fileName + ".vs");
	if (fragment == "")
	{
		fragment = LoadShader(fileName + ".fs");
		
	}

	currentFragmentString = fragment;

	succes = true;
	m_shaders[0] = CreateShader(vertex, GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(fragment, GL_FRAGMENT_SHADER);

	if (!succes)
		return false;


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
	RegisterUniform("LightDirStatic");
	RegisterUniform("LightColor");
	RegisterUniform("LightDiffuseIntensity");
	RegisterUniform("LightAmbientIntensity");

	std::cout << "Shading Program " << m_program << " Created: " << m_uniformLocations.size() << " uniforms" << std::endl;
	return true;
}

Shader::Shader(){}
//Shader::Shader(const std::string& fileName)
//{
//	
//	
//
//
//}
//
//
//Shader::Shader(const std::string& fragmentCode, bool usingCode)
//{
//	m_program = glCreateProgram();
//	std::string vertexFile = "../../Resources/Shaders/phongNormalShader.vs";
//
//	m_shaders[0] = CreateShader(LoadShader(vertexFile), GL_VERTEX_SHADER);			// carga el standard VS
//	m_shaders[1] = CreateShader(fragmentCode , GL_FRAGMENT_SHADER);					// carga solo el fragment
//
//	for (unsigned int i = 0; i < NUM_SHADERS; i++)
//		glAttachShader(m_program, m_shaders[i]);
//
//
//	
//	glBindAttribLocation(m_program, 0, "VertexPosition");
//	glBindAttribLocation(m_program, 1, "VertexTexCoord");
//	glBindAttribLocation(m_program, 2, "VertexNormal");
//	glBindAttribLocation(m_program, 4, "VertexTangent");
//
//	glLinkProgram(m_program);
//	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Shader linking failed: ");
//
//	glValidateProgram(m_program);
//	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Invalid shader program ");
//
//
//	RegisterUniform("ModelViewMatrix");
//	RegisterUniform("NormalMatrix");
//	RegisterUniform("ProjectionMatrix");
//	RegisterUniform("MVP");
//	/*RegisterUniform("ColorTex");
//	RegisterUniform("NormalMapTex");
//	RegisterUniform("SpecularMapTex");
//	RegisterUniform("Material.Ka");
//	RegisterUniform("Material.Ks");
//	RegisterUniform("Material.Shininess");*/
//	//RegisterUniform("Model");
//	//RegisterUniform("MAX_NUM_LIGHTS");
//	//RegisterUniform("AtteConstantTest");
//	//RegisterUniform("AtteLinearTest");
//	//RegisterUniform("AtteExpTest");
//	RegisterUniform("LightDirStatic");
//	RegisterUniform("LightColor");
//	RegisterUniform("LightDiffuseIntensity");
//	RegisterUniform("LightAmbientIntensity");
//
//
//	std::cout << "Shading Program " << m_program << " Created: " << m_uniformLocations.size() << " uniforms" << std::endl;
//
//}

void Shader::RegisterUniform(const char *name)
{
	int uniform = glGetUniformLocation(m_program, name);
	if (uniform == -1)
		std::cout << "Error getting uniform location: " << name << endl;

	m_uniforms.push_back(uniform);
	m_uniformLocations.insert(std::pair<std::string, int>(name, uniform));
	uniformIndex++;
	std::cout << "Uniform Registered: " << name << endl;

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



void Shader::Update(Transform& transform, Camera& camera)
{

	
	// Send the data for the graphics card
	glm::mat4 M = transform.GetModel();
	glm::mat4 P = camera.GetProjection();
	glm::mat4 V = camera.GetView();					// Get The View Matrix
	glm::mat4 VP = camera.GetViewProjection();		// Get The ViewProjection
	glm::mat4 MV = V * M;									// Get The ModelView 
	glm::mat4 MVP = P * V * M;								// Get The ModelViewProjection Matrix
	glm::mat3 N(glm::transpose(glm::inverse(MV)));			// Get The Normal Matrix
	
	//glm::mat4 MVP = transform.GetMVP(camera);
	//glm::mat4 ModelView = camera.GetView() * transform.GetModel();
	//glm::mat4 Normal = transform.GetModel();
	


	//SetUniform("ProjectionMatrix", P);
	
	//SetUniform("ModelViewMatrix", ModelView);
	//SetUniform("NormalMatrix", Normal);
	SetUniform("ProjectionMatrix", P);
	// Send matrices to the shader
	SetUniform("ModelViewMatrix", MV);
	SetUniform("NormalMatrix", N);
	SetUniform("MVP", MVP);
	//SetUniform("MVP", MVP);
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
	//cout << "Location = " << loc << endl;

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


string Shader::GetFragmentString()
{
	return currentFragmentString;
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
