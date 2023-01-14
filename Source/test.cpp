#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

import Sandcore.Shader.Program;
import Sandcore.Window;
import Sandcore.Mesh;
import Sandcore.Event;
import Sandcore.Graphics.Texture2D;
import Sandcore.Framebuffer.Vertex;

using namespace Sandcore;

int main() {
	int width = 700;
	int height = 700;
	Window window(width, height, "Test Window");
	window.setContext();
	window.setCurrent();
	Event event;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Texture2D texture0, texture3;
	texture0.loadFromFile("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/texture_package/A.png");
	texture3.loadFromFile("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/texture_package/B.png");

	ShaderProgram screenShader("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/shaders/screen_shader");
	Mesh<FramebufferVertex> mesh;
	mesh.vertices = { {0}, {1}, {2}, {3} };
	mesh.indices = { 0,1,2,0,2,3 };
	mesh.update();

	while (!window.isShouldClose()) {
		window.pollEvent(event);

		window.getSize(&width, &height);

		window.clear();
		glViewport(0, 0, width / 2.f, height / 2.f);
		window.draw(mesh, screenShader, texture0);
		glViewport(width / 2.f, height / 2.f, width / 2.f, height / 2.f);
		window.draw(mesh, screenShader, texture3);
		window.display();
	}
}