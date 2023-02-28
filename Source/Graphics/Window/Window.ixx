#include <GLFW/glfw3.h>

export module Sandcore.Window;

import Sandcore.Graphics.Canvas;
import Sandcore.Event;
import Sandcore.Image;

export namespace Sandcore {
	class Window : public Canvas {
	public:
		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		
		~Window();

		bool pollEvent(Event& event);

		void setContext();
		void setCurrent();

		void getFramebufferSize(int* width, int* height);
		void getSize(int* width, int* height);

		void getMouse(double* x, double* y);
		bool getKey(int key);

		void setMouseDisabled();
		void setMouseEnabled();

		bool isOpen();
		void close();

		void display();

		void setIcon(Image& image);

		operator GLFWwindow*();

	private:
		virtual void bindFramebuffer();

		GLFWwindow* window = nullptr;
		void create(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	};
}