#pragma once

#include <string>
#include <gl/glew.h>

class Shader
{
public:
	
	Shader(const std::string& fileName);
	
	void Bind();
	
	virtual ~Shader();

private:

	static const unsigned int NUM_SHADERS = 2;

	GLuint _program;
	GLuint _shaders[NUM_SHADERS]; 

private:

	Shader(const Shader& other);
	
	void operator=(const Shader& other);

};
