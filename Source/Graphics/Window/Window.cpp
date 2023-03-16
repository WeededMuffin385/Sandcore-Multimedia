#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <unordered_map>
import Sandcore.Window;

import Sandcore.Event;
import Sandcore.Image;

namespace Sandcore {
	Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
		static bool glfwinit = glfwInit();
		window = glfwCreateWindow(width, height, title, monitor, share);

		glfwMakeContextCurrent(window);
		glewExperimental = GL_TRUE;
		glewInit();
	}

	Window::~Window() {
		Event::erase(window);
		glfwDestroyWindow(window);
	}

	bool Window::pollEvent(Event& event) {
		return Event::pollEvent(window, event);
	}

	void Window::setIcon(Image& image) {
		GLFWimage icon;
		icon.pixels = image.data();
		icon.width = image.size().x;
		icon.height = image.size().y;
		glfwSetWindowIcon(window, 1, &icon);
	}

	void Window::setContext() {
		glfwMakeContextCurrent(window);
	}

	Vector2D<int> Window::getSize() {
		int x, y;
		glfwGetWindowSize(window, &x, &y);
		return { x, y };
	}

	Vector2D<double> Window::mouse() {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { x ,y };
	}

	bool Window::getMouseButton(int button, int state) {
		return glfwGetMouseButton(window, button) == state;
	}

	bool Window::getKey(int key, int state) {
		return glfwGetKey(window, key) == state;
	}

	bool Window::isOpen() {
		return !glfwWindowShouldClose(window);
	}

	void Window::display() {
		glfwSwapBuffers(window);
	}

	void Window::toggleCursor(Cursor mode) {
		glfwSetInputMode(window, GLFW_CURSOR, mode);
	}
}