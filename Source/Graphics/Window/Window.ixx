#include <GLFW/glfw3.h>

export module Sandcore.Window;

import Sandcore.Event;

export namespace Sandcore {
	class Window {
	public:
		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		bool pollEvent(Event& event);

		void create(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
		void destroy();

		void setContext();
		void setCurrent();
		void getFramebufferSize(int* width, int* height);
		void getSize(int* width, int* height);
		void getMouse(double* x, double* y);
		bool getKey(int key);
		void setMouseDisabled();
		void setMouseEnabled();

		bool shouldClose();
		void close();
		void swapBuffers();

		GLFWwindow* window = nullptr;
	private:
	};
}