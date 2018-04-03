#include "Mesh.h"

#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	this->_drawCount = numVertices;

	glGenVertexArrays(1, &(this->_vertexArrayObject));

	glBindVertexArray(this->_vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for(unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*(vertices[i].getPos()));
		texCoords.push_back(*(vertices[i].getTexCoord()));
	}
	
	glGenBuffers(NUM_BUFFERS, this->_vertexArrayBuffers);
	
	// Cues OpenGL to interpret our buffer memory as an array structure;

	glBindBuffer(GL_ARRAY_BUFFER, this->_vertexArrayBuffers[POSITION_VB]);

	// Load our buffer data into GPU memory;

	// Note that GL_STATIC_DRAW indicates that the buffer we're 
	// providing will not change, allowing OpenGL to potentially
	// optimize where it stores the buffer data on the GPU (i.e.,
	// some place that is fast to read from but perhaps slow to write to);

	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]),
		&positions[0], GL_STATIC_DRAW);

	// Allows us to start defining some characteristics of an
	// attrib array with ID 0;

	glEnableVertexAttribArray(0);

	// For attrib array '0', each attribute entry will have
	// three items, each a floating-point value, in which these
	// items (triplets) are contiguous in the buffer, and the
	// first item begins at the very beginning of the buffer;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// glBindVertexArray(0);

	// Similar setup for texture coordinates

	glBindBuffer(GL_ARRAY_BUFFER, this->_vertexArrayBuffers[TEXCOORD_VB]);

	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]),
		&texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Stop implicitly referring to this specific vertex array;
	// (disconnecting from this specific vertex array context);

	//glBindVertexArray(1);
	glBindVertexArray(0);
	
}

void Mesh::Draw()
{
	glBindVertexArray(this->_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, this->_drawCount);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &(this->_vertexArrayObject));
}

void Mesh::operator=(const Mesh & other)
{

}
