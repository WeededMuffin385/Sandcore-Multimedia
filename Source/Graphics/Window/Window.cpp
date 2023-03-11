#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <stdexcept>
import Sandcore.Window;

import Sandcore.Event;
import Sandcore.Image;

namespace Sandcore {
	const char* get_source_string(GLenum source) {
		switch (source) {
		case GL_DEBUG_SOURCE_API:
			return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return "Window System";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return "Shader Compiler";
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return "Third Party";
		case GL_DEBUG_SOURCE_APPLICATION:
			return "Application";
		case GL_DEBUG_SOURCE_OTHER:
			return "Other";
		default:
			return "Unknown";
		}
	}

	const char* get_type_string(GLenum type) {
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			return "Error";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return "Deprecated Behavior";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return "Undefined Behavior";
		case GL_DEBUG_TYPE_PORTABILITY:
			return "Portability";
		case GL_DEBUG_TYPE_PERFORMANCE:
			return "Performance";
		case GL_DEBUG_TYPE_MARKER:
			return "Marker";
		case GL_DEBUG_TYPE_PUSH_GROUP:
			return "Push Group";
		case GL_DEBUG_TYPE_POP_GROUP:
			return "Pop Group";
		case GL_DEBUG_TYPE_OTHER:
			return "Other";
		default:
			return "Unknown";
		}
	}

	const char* get_severity_string(GLenum severity) {
		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			return "High";
		case GL_DEBUG_SEVERITY_MEDIUM:
			return "Medium";
		case GL_DEBUG_SEVERITY_LOW:
			return "Low";
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			return "Notification";
		default:
			return "Unknown";
		}
	}

	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam) {

		std::cout << "OpenGL Debug - Source: " << get_source_string(source)
			<< "| Type: " << get_type_string(type)
			<< "| Severity: " << get_severity_string(severity)
			<< "| Message: " << message << std::endl;
		if (severity == GL_DEBUG_SEVERITY_HIGH) throw std::exception("OPENGL ERROR");
	}

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

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
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