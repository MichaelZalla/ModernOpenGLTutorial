#include <fstream>
#include <iostream>

#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

// Forward-declare some static utility functions

static GLuint CreateShader(const std::string& text, GLenum shaderType);
static std::string GetShaderFileAsText(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

Shader::Shader(const std::string& fileName)
{
	// Allocate some GPU memory to store a new program

	this->_program = glCreateProgram();

	// Read the specified shader programs off of disk,
	// following our own implicit file-naming conventions;

	this->_shaders[0] = CreateShader(
		GetShaderFileAsText(fileName + ".vert.gsh"),
		GL_VERTEX_SHADER);
	
	this->_shaders[1] = CreateShader(
		GetShaderFileAsText(fileName + ".frag.gsh"),
		GL_FRAGMENT_SHADER);

	// Ask OpenGL to associated each shader with our
	// allocated program;

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(this->_program, this->_shaders[i]);
	}

	glBindAttribLocation(this->_program, 0, "position");
	glBindAttribLocation(this->_program, 1, "texCoord");
	glBindAttribLocation(this->_program, 2, "normal");

	glLinkProgram(this->_program);

	CheckShaderError(this->_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(this->_program);

	CheckShaderError(this->_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed: ");

	// Get the 'transform' uniform's (CPU) memory location 
	// so we can write to it;
	
	// @TODO(mzalla) Technically _uniforms stores GLuints; check 
	// whether getGetUniformLocation is giving us a pointer value;

	this->_uniforms[TRANSFORM_UNIFORM] = glGetUniformLocation(this->_program, "transform");

}

void Shader::Bind()
{
	glUseProgram(this->_program);
}

void Shader::Update(const Camera& camera, const Transform& transform)
{
	glm::mat4 model = camera.getViewProjection() * transform.getModel();

	glUniformMatrix4fv(this->_uniforms[TRANSFORM_UNIFORM], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(this->_program, this->_shaders[i]);
		glDeleteShader(this->_shaders[i]);
	}

	glDeleteProgram(this->_program);
}

// void Shader::operator=(const Shader& other)
// {
// }

GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if(shader == 0)
	{
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];

	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();

	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

std::string GetShaderFileAsText(const std::string& fileName)
{
	std::ifstream file;

	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;

}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	
	if(isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE)
	{
		if(isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
