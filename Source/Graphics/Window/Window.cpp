#include <GLFW/glfw3.h>

import Sandcore.Window;

import Sandcore.Event;

namespace Sandcore {
	Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
		create(width, height, title, monitor, share);
	}

	void Window::create(int width, int height, const char*title, GLFWmonitor*monitor, GLFWwindow*share) {
		glfwWindowHint(GLFW_SAMPLES, 4);
		window = glfwCreateWindow(width, height, title, monitor, share);
	}

	bool Window::pollEvent(Event& event) {
		return Event::pollEvent(event, window);
	}

	void Window::destroy() {
		glfwDestroyWindow(window);
	}

	void Window::setContext() {
		glfwMakeContextCurrent(window);
	}

	void Window::setCurrent() {
		Event::setCurrent(window);
	}

	void Window::getFramebufferSize(int*width, int*height) {
		glfwGetFramebufferSize(window, width, height);
	}

	void Window::getSize(int* width, int* height) {
		glfwGetWindowSize(window, width, height);
	}

	void Window::getMouse(double* x, double* y) {
		glfwGetCursorPos(window, x, y);
	}

	bool Window::getKey(int key) {
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}

	void Window::close() {
		return glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(window);
	}

	void Window::setMouseDisabled() {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::setMouseEnabled() {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}