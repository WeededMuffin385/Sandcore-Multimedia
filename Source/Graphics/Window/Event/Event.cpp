#include <queue>
#include <unordered_map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Event;

namespace Sandcore {
	std::unordered_map<GLFWwindow*, std::queue<Event>> Event::events;

	bool Event::pollEvent(GLFWwindow* window, Event& event) {
		setCurrentWindow(window);
		auto& queue = events[window];
		glfwPollEvents();

		if (queue.empty()) return false;
		event = queue.front();
		queue.pop();
		return true;
	}

	void Event::setCurrentWindow(GLFWwindow* window) {
		if (!events.contains(window)) setWindowCallback(window);
	}

	void Event::setWindowCallback(GLFWwindow* window) {
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
	}

	void Event::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Event event = {
			.type = Event::Type::Cursor,
			.cursor = {
				.x = xpos,
				.y = ypos
			}
		};

		events[window].push(event);
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

		events[window].push(event);
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

		events[window].push(event);
	}

	void Event::window_size_callback(GLFWwindow* window, int width, int height) {
		Event event = {
			.type = Event::Type::Window,
			.window = {
				.width = width,
				.height = height,
			}
		};

		events[window].push(event);
	}
}