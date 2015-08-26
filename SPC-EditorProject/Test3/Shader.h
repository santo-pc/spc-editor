#pragma once
#include <string>
#include <GL/glew.h>
#include "Camera.h"
#include "Transform.h"
#include <vector>
#include <map>
#include "Utils.h"



class Shader
{

public:
	Shader();
	virtual ~Shader();
	/*Shader(const std::string& fileName);
	Shader(const std::string& fragmentCode, bool usingCode);*/
	void Bind();
	bool Load(const std::string& fileName, std::string vertex, std::string fragment);
	GLuint CreateShader(const std::string& text, GLenum type);
	bool CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	//void Update(const glm::mat4 MVP, const glm::mat4 model, glm::vec3 color);
	GLuint GetProgramHandler();
	void SetUniform(const char *name, float x, float y, float z);
	void SetUniform(const char *name, const glm::vec2 & v);
	void SetUniform(const char *name, const glm::vec3 & v);
	void SetUniform(const char *name, const glm::vec4 & v);
	void SetUniform(const char *name, const glm::mat4 & m);
	void SetUniform(const char *name, const glm::mat3 & m);
	void SetUniform(const char *name, float val);
	void SetUniform(const char *name, int val);
	void SetUniform(const char *name, bool val);
	void SetUniform(const char *name, GLuint val);
	void Update(Transform& transform, Camera& camera);
	void RegisterUniform(const char *name);
	bool succes = true;


protected:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	std::vector<GLuint> m_uniforms;
	std::map<std::string, int> m_uniformLocations;
	int GetUniformLocation(const char * name);
	int uniformIndex = 0;
	GLuint m_program;
private:

	GLuint m_shaders[NUM_SHADERS];
	//GLuint m_uniforms[NUM_UNIFORMS];


};



#define GLOBAL_CONTAIER GlobalContainer::Instance()
class GlobalContainer
{
private:
	GlobalContainer();
	~GlobalContainer();

public:
	static GlobalContainer * Instance();
	Shader * GlobalShader;
	Shader * GlobalErrorShader;
	
};
