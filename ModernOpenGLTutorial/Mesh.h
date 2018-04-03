#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>

class Vertex
{
public:

	Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	{
		this->_pos = position;
		this->_texCoord = texCoord;
	}

	inline glm::vec3* getPos()
	{
		return &(this->_pos);
	}

	inline glm::vec2* getTexCoord()
	{
		return &(this->_texCoord);
	}

private:

	glm::vec3 _pos;
	glm::vec2 _texCoord;

};

class Mesh
{
public:
	
	Mesh(Vertex* vertices, unsigned int numVertices);

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
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];

	unsigned int _drawCount;

private:

	Mesh(const Mesh& other);

	void operator=(const Mesh& other);

};
 