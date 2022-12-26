#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

import Sandcore.Shader.Program;
import Sandcore.Window;
import Sandcore.Mesh;
import Sandcore.Event;
import Sandcore.Texture;
import Sandcore.Framebuffer.Vertex;

using namespace Sandcore;

int main() {
	Window window(700, 700, "Test Window");
	window.setContext();
	window.setCurrent();
	Event event;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Texture texture0, texture3;
	texture0.loadFromFile("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/texture_package/A.png");
	texture3.loadFromFile("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/texture_package/B.png");

	ShaderProgram screenShader("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/shaders/screen_shader");
	Mesh<FramebufferVertex> mesh;
	mesh.vertices = { {0}, {1}, {2}, {3} };
	mesh.indices = { 1,0,2,1,2,3 };
	mesh.update();

	while (!window.isShouldClose()) {
		window.pollEvent(event);

		window.clear();
		texture0.bind();
		window.draw(mesh, screenShader);
		texture3.bind();
		window.draw(mesh, screenShader);
		window.display();
	}
}