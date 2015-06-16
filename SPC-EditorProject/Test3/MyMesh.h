#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

struct MyVertex
{
public:
	MyVertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class MyMesh
{
	public:
		MyMesh(const std::string& fileName);
		MyMesh(MyVertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

		void Draw();

		virtual ~MyMesh();
	protected:
	private:
		static const unsigned int NUM_BUFFERS = 4;
		void operator=(const MyMesh& mesh) {}
		MyMesh(const MyMesh& mesh) {}

		void InitMesh(const IndexedModel& model);

		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_numIndices;
};
