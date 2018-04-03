#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>

class Vertex
{
public:

	Vertex(const glm::vec3& position)
	{
		this->_pos = position;
	}

private:

	glm::vec3 _pos;

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
	// given a numeric value equal to the number of enums
	// previously defined;

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];

	unsigned int _drawCount;

private:

	Mesh(const Mesh& other);

	void operator=(const Mesh& other);

};
 