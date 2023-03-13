#include <filesystem>

#include <asio.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Application;

import Sandcore.Engine;
import Sandcore.Window;
import Sandcore.Image;
import Sandcore.MainMenu;
import Sandcore.Engine;
import Sandcore.Event;

namespace Sandcore {
	Application::Application() : window(800, 600, "Sandcore Multimedia") {
		Image image("C:/Workbench/Sandcore/Resources/logo.png");
		window.setIcon(image);

		push(new MainMenu(window, event, scenes));
	}

	void Application::tick() {
		scenes.top()->tick();
		if (!scenes.top()->run) scenes.pop();
	}

	void Application::loop() {
		while (!scenes.empty() && window.isOpen()) {
			tick();
		}
	}

	void Application::push(Scene* scene) {
		scenes.push(std::unique_ptr<Scene>(scene));
	}
}