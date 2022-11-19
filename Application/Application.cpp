#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

import Sandcore.Application;

import Sandcore.Engine;
import Sandcore.Window;
import Sandcore.Image;

namespace Sandcore {
	Application::Application() : window(800, 600, "Sandcore Multimedia") {
		window.setContext();
		window.setCurrent();

		Image image("C:/Workbench/Sandcore/Resources/logo.png");
		window.setIcon(image);

		int width, height;
		window.getFramebufferSize(&width, &height);

		scenes.push(new Engine(window, event));
	}

	void Application::loop() {
		while (!scenes.isEmpty() && !window.isShouldClose()) {
			scenes.tick();
		}
	}
}