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
import Sandcore.Graphics.Debug;

namespace Sandcore {
	Application::Application() : window(800, 600, "Sandcore Multimedia") {
		Image image("C:/Workbench/Sandcore/Resources/logo.png");
		window.setIcon(image);
		debugInit();

		Event::foo = &foo;

		push(new MainMenu(window, event, scenes));
	}

	void Application::tick() {
		if (!scenes.top()->run) {
			scenes.pop();
			return;
		}
		scenes.top()->tick();
	}

	void Application::loop() {
		while (!scenes.empty() && window.isOpen()) {
			application = this;
			tick();
		}
	}

	void Application::push(Scene* scene) {
		scenes.push(std::unique_ptr<Scene>(scene));
	}

	void Application::foo() {
		application->tick();
	}
}