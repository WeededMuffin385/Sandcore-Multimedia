#include <queue>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Event;
import Sandcore.Scene;

namespace Sandcore {
	GLFWwindow* Event::current = nullptr;
	Scene* Event::scene = nullptr;
	std::queue<Event> Event::events = {};

	bool Event::pollEvent(GLFWwindow* window, Event& event) {
		if (window != current) setCurrentWindow(window);
		glfwPollEvents();

		if (events.empty()) return false;
		event = events.front();
		events.pop();
		return true;
	}

	void Event::setCurrentWindow(GLFWwindow* window) {
		if (current) removeWindowCallback(current);
		setWindowCallback(window);

		current = window;
		events = {};
	}


	void Event::setWindowCallback(GLFWwindow* window) {
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}

	void Event::removeWindowCallback(GLFWwindow* window) {
		glfwSetCursorPosCallback(window, NULL);
		glfwSetMouseButtonCallback(window, NULL);
		glfwSetKeyCallback(window, NULL);
		glfwSetWindowSizeCallback(window, NULL);
		glfwSetFramebufferSizeCallback(window, NULL);
	}

	void Event::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Event event = {
			.type = Event::Type::Cursor,
			.cursor = {
				.x = xpos,
				.y = ypos
			}
		};

		events.push(event);
	}

	void Event::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
		Event event = {
			.type = Event::Type::Mouse,
			.mouse = {
				.button = button,
				.action = action,
				.mode = mode
			}
		};

		events.push(event);
	}

	void Event::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		Event event = {
			.type = Event::Type::Key,
			.key = {
				.key = key,
				.scancode = scancode,
				.action = action,
				.mode = mode
			}
		};

		events.push(event);
	}

	void Event::window_size_callback(GLFWwindow* window, int width, int height) {
		Event event = {
			.type = Event::Type::Window,
			.window = {
				.width = width,
				.height = height,
			}
		};

		events.push(event);
	}

	void Event::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		if (scene) scene->tick();
	}
}