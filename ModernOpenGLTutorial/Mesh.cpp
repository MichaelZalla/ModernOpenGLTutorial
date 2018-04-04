#include <vector>

#include "obj_loader.h"
#include "Mesh.h"

Mesh::Mesh(const std::string & fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();

	this->InitMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	model.positions.reserve(numVertices);
	model.texCoords.reserve(numVertices);
	model.normals.reserve(numVertices);
	
	for(unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].getTexCoord());
		model.normals.push_back(*vertices[i].getNormal());
	}

	model.indices.reserve(numIndices);

	for(unsigned int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}

	this->InitMesh(model);

}

void Mesh::Draw()
{
	glBindVertexArray(this->_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, this->_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &(this->_vertexArrayObject));
}

void Mesh::InitMesh(const IndexedModel& model)
{
	this->_drawCount = model.indices.size();

	glGenVertexArrays(1, &(this->_vertexArrayObject));

	glBindVertexArray(this->_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, this->_vertexArrayBuffers);

	// Cues OpenGL to interpret our buffer memory as an array structure;

	glBindBuffer(GL_ARRAY_BUFFER, this->_vertexArrayBuffers[POSITION_VB]);

	// Load our buffer data into GPU memory;

	// Note that GL_STATIC_DRAW indicates that the buffer we're 
	// providing will not change, allowing OpenGL to potentially
	// optimize where it stores the buffer data on the GPU (i.e.,
	// some place that is fast to read from but perhaps slow to write to);

	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]),
		&model.positions[0], GL_STATIC_DRAW);

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

	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]),
		&model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Similar setup for face indices

	glBindBuffer(GL_ARRAY_BUFFER, this->_vertexArrayBuffers[NORMAL_VB]);

	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]),
		&model.normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Similar setup for face indices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vertexArrayBuffers[INDEX_VB]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]),
		&model.indices[0], GL_STATIC_DRAW);

	// Stop implicitly referring to this specific vertex array;
	// (disconnecting from this specific vertex array context);

	glBindVertexArray(0);
}
