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
		glfwWindowHint(GLFW_SAMPLES, 4);
		window = glfwCreateWindow(width, height, title, monitor, share);
	}

	bool Window::pollEvent(Event& event) {
		return Event::pollEvent(event, window);
	}

	void Window::setCurrent() {
		return Event::setCurrentWindow(window);
	}

	void Window::setIcon(Image& image) {
		GLFWimage icon;
		icon.pixels = image.data();
		icon.width = image.size.x;
		icon.height = image.size.y;
		glfwSetWindowIcon(window, 1, &icon);
	}

	void Window::setContext() {
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();
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

	bool Window::isShouldClose() {
		return glfwWindowShouldClose(window);
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