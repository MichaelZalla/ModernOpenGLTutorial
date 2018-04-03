#pragma once

#include <string>
#include <gl/glew.h>

class Texture
{
public:
	
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);
	
	virtual ~Texture();
	
private:

	GLuint _texture;

	// Texture(const Texture& other);
	
	// Texture& operator=(const Texture& other);

};
