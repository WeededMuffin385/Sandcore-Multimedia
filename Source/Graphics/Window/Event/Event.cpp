#include <queue>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Event;

namespace Sandcore {
	GLFWwindow* Event::current;
	std::queue<Event> Event::events;

	bool Event::pollEvent(Event& event, GLFWwindow* window) {
		if (window != current) setCurrent(window);
		glfwPollEvents();

		if (events.empty()) return false;
		event = events.front();
		events.pop();
		return true;
	}

	void Event::setCurrent(GLFWwindow* window) {
		current = window;
		events = {};
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
	}

	void Event::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Event event = {
			.type = Event::Type::cursor,
			.cursor = {
				.x = xpos,
				.y = ypos
			}
		};

		events.push(event);
	}

	void Event::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
		Event event = {
			.type = Event::Type::mouse,
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
			.type = Event::Type::key,
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
			.type = Event::Type::window,
			.window = {
				.width = width,
				.height = height,
			}
		};

		events.push(event);
	}
}