#pragma once
#include <string>
#include <GL/glew.h>
#include "Camera.h"
#include "Transform.h"
#include <vector>
#include <map>



//class Shader
//{
//	public:
//		Shader(const std::string& fileName);
//
//		void Bind();		
//		void Update(const Transform& transform, const Camera& camera);
//
//
//		virtual ~Shader();
//	protected:
//	private:
//		static const unsigned int NUM_SHADERS = 2;
//		static const unsigned int NUM_UNIFORMS = 3;
//		//static const unsigned int NUM_UNIFORMS = 3;
//		void operator=(const Shader& shader) {}
//		Shader(const Shader& shader) {}
//
//		/*GLuint CreateShader(const std::string& text, unsigned int type);
//		std::string LoadShader(const std::string& fileName);
//		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);*/
//		
//
//
//		GLuint m_program;
//		GLuint m_shaders[NUM_SHADERS];
//		GLuint m_uniforms[NUM_UNIFORMS];
//		
//};

class Shader
{

public:
	Shader();
	virtual ~Shader();
	Shader(const std::string& fileName);
	void Bind();

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
	void Update(const Transform& transform, const Camera& camera);



protected:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	std::vector<GLuint> m_uniforms;
	std::map<std::string, int> m_uniformLocations;
	int GetUniformLocation(const char * name);
	void RegisterUniform(const char *name);
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
};
