#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLFW/glfw3.h>

#include <memory>

import Sandcore.Window;

import Sandcore.Event;
import Sandcore.Image;

namespace Sandcore {
	Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
		glfwInit();
		create(width, height, title, monitor, share);

		static bool first = true;
		if (first) [[unlikely]] {
			setContext();
			setCurrent();
			init();
			first = false;
		}
	}

	void Window::init() {
		glewExperimental = GL_TRUE;
		glewInit();
	}

	Window::~Window() {
		glfwDestroyWindow(window);
	}

	Window::operator GLFWwindow*() {
		return window;
	}

	void Window::bindFramebuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Window::create(int width, int height, const char*title, GLFWmonitor*monitor, GLFWwindow*share) {
		window = glfwCreateWindow(width, height, title, monitor, share);
		glfwSwapInterval(1);
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

	void Window::setCurrent() {
		Event::setCurrentWindow(window);
	}

	void Window::getFramebufferSize(int*width, int*height) {
		glfwGetFramebufferSize(window, width, height);
	}

	Window::Size Window::size() {
		int x;
		int y;
		glfwGetWindowSize(window, &x, &y);

		return Size(x, y);
	}

	Window::Mouse Window::mouse() {
		double x;
		double y;
		glfwGetCursorPos(window, &x, &y);

		return Mouse(x, y);
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

	void Window::close() {
		return glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void Window::display() {
		glfwSwapBuffers(window);
	}

	void Window::setMouseDisabled() {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::setMouseEnabled() {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}