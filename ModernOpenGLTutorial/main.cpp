#include <glm/glm.hpp>

#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "SDL 2.0.8 Window Demo");
	
	/*
	Vertex vertices[] = {
		Vertex(
			glm::vec3(-0.5, -0.5, 0),
			glm::vec2(0.0, 1.0)
		),
		Vertex(
			glm::vec3(0, 0.5, 0),
			glm::vec2(0.5, 0.0)
		),
		Vertex(
			glm::vec3(0.5, -0.5, 0),
			glm::vec2(1.0, 1.0)
		)
	};

	unsigned int indices[] = {
		0,
		1,
		2,
	};
	*/
	
	//Mesh mesh(
	//	vertices, sizeof(vertices) / sizeof(vertices[0]),
	//	indices, sizeof(indices) / sizeof(indices[0])
	//);

	Mesh mesh("./res/lampost.obj");

	Shader shader("./res/basicShader");
	
	Texture texture("./res/bricks.jpg");

	Camera camera(glm::vec3(0, 0, -16), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

	Transform transform;

	float counter = 0.0f;
	
	while(!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = 1.0f + 0.5f * cosf(counter);

		shader.Bind();

		texture.Bind(0);

		transform.getPos().x = sinf(counter);
		transform.getPos().z = cosf(counter);
		
		transform.getRot().x = counter;
		transform.getRot().y = counter;
		transform.getRot().z = counter;
		
		transform.getScale() = glm::vec3(cosCounter, cosCounter, cosCounter);
		
		shader.Update(camera, transform);
		
		// mesh.Draw();

		mesh.Draw();
		
		display.Update();

		counter += 0.003f;
	}

	return 0;
}
 