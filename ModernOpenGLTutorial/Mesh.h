#pragma once

#include <string>
#include <glm/glm.hpp>
#include <gl/glew.h>

#include "obj_loader.h"

class Vertex
{
public:

	Vertex(const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->_pos = position;
		this->_texCoord = texCoord;
		this->_normal = normal;
	}

	inline glm::vec3* getPos()
	{
		return &(this->_pos);
	}

	inline glm::vec2* getTexCoord()
	{
		return &(this->_texCoord);
	}

	inline glm::vec3* getNormal()
	{
		return &(this->_normal);
	}

private:

	glm::vec3 _pos;
	glm::vec2 _texCoord;
	glm::vec3 _normal;

};

class Mesh
{
public:
	
	Mesh(const std::string& fileName);

	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

	void Draw();
	
	virtual ~Mesh();

private:

	// Create enums for each buffer in _vertexArrayBuffers,
	// ending with a "size" enum that just-so-happens to be
	// given a numeric value equal to the number of prior
	// enum entries;

	enum
	{
		POSITION_VB,
		INDEX_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;

	GLuint _vertexArrayBuffers[NUM_BUFFERS];

	unsigned int _drawCount;

private:

	Mesh(const Mesh& other);

	void InitMesh(const IndexedModel& model);

};
 