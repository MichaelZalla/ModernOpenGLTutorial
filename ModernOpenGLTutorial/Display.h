#pragma once

#include <iostream>
#include <string>
#include "sdl2\SDL.h"

class Display
{
public:
	
	Display(int width, int height, const std::string& title);

	bool isClosed();

	void Clear(float r, float g, float b, float a);

	void Update();
	
	virtual ~Display();

private: 

	bool _isClosed;

	SDL_Window* _window;

	SDL_GLContext _glContext;
	
private:

	Display(const Display& other);
	
	Display& operator=(const Display& other);

};
