#include "Display.h"
#include "Mesh.h"
#include "Shader.h"

int main(int argc, char** argv)
{
	Display display(800, 600, "SDL 2.0.8 Window Demo");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0)),
		Vertex(glm::vec3(0, 0.5, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0)),
	};
		
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./res/basicShader");

	while(!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();
		
		mesh.Draw();
		
		display.Update();
	}

	return 0;
}
