#pragma once

#include <string>

#include <gl/glew.h>

#include "Transform.h"

class Shader
{
public:
	
	Shader(const std::string& fileName);
	
	void Bind();

	void Update(const Transform& transform);
	
	virtual ~Shader();

private:

	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_UNIFORM,
		NUM_UNIFORMS,
	};

	GLuint _program;
	GLuint _shaders[NUM_SHADERS]; 
	GLuint _uniforms[NUM_UNIFORMS];

private:

	// Shader(const Shader& other);
	
	// void operator=(const Shader& other);

};
