#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

import Sandcore.Window;
import Sandcore.Event;

import Sandcore.World;
import Sandcore.Engine;

using namespace Sandcore;

int main() {
	std::cout << "Compiled on: " __DATE__ << " " << __TIME__ << "\n";

	glfwInit();
	Window window(800, 600, "Sandcore Multimedia");

	window.setContext();
	window.setCurrent();

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	window.getFramebufferSize(&width, &height);
	glViewport(0, 0, width, height);

	Event event;

	Engine engine(window, event);

	while (!window.shouldClose()) {
		engine.tick();
	}
}