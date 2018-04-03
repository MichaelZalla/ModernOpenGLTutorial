#include "Display.h"

int main(int argc, char** argv)
{
	Display display(640, 480, "SDL 2.0.8 Window Demo");

	while(!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		display.Update();
	}

	return 0;
}
