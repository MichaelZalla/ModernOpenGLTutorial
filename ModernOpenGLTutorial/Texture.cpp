#include "Texture.h"

#include <iostream>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& fileName)
{
	int width;
	int height;

	int numComponents;

	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if(imageData == 0)
	{
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
	}

	glGenTextures(1, &(this->_texture));

	glBindTexture(GL_TEXTURE_2D, this->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	assert(imageData != 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	assert(imageData != 0);

	stbi_image_free(imageData);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	// Bind our texture to a texture unit, by specifying the active
	// texture unit in OpenGL before calling glBindTexture;

	glActiveTexture(GL_TEXTURE0 + unit);

	glBindTexture(GL_TEXTURE_2D, this->_texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &(this->_texture));
}

//Texture::Texture(const Texture & other)
//{
//
//}
//
//Texture & Texture::operator=(const Texture & other)
//{
//
//}
