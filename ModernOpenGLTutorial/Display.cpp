#include "Display.h"
#include <iostream>
#include <gl/glew.h>

Display::Display(int width, int height, const std::string & title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);

	this->_glContext = SDL_GL_CreateContext(this->_window);

	// Prompt the GLEW lib to scan our system for any supported
	// OpenGL capabilities; GLEW returns a status enum to report
	// how things went...

	GLenum status = glewInit();

	if(status != GLEW_OK)
	{
		std::cerr << "GLEW failed to intialize!" << std::endl;
	}

	this->_isClosed = false;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
}

bool Display::isClosed()
{
	return this->_isClosed;
}

void Display::Update()
{
	SDL_GL_SwapWindow(this->_window);

	SDL_Event e;

	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			this->_isClosed = true;
		}
	}
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glClear(GL_DEPTH_BUFFER_BIT);
}

Display::~Display()
{
	SDL_GL_DeleteContext(this->_glContext);

	SDL_DestroyWindow(this->_window);

	SDL_Quit();
}

Display::Display(const Display& other)
{
	// Copy constructor
}

Display& Display::operator=(const Display& rhs)
{
	
	// Assignment op

	if(this == &rhs)
	{
		return *this;
	}

	return *this;

}
