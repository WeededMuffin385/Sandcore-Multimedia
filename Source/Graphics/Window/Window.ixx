#include <GLFW/glfw3.h>

export module Sandcore.Window;

import Sandcore.Graphics.Canvas;
import Sandcore.Event;
import Sandcore.Image;

export namespace Sandcore {
	class Window : public Canvas {
	public:
		struct Size {
			int x;
			int y;
		};

		struct Mouse {
			double x;
			double y;
		};
	public:
		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		
		~Window();

		bool pollEvent(Event& event);

		void setContext();
		void setCurrent();

		void getFramebufferSize(int* width, int* height);

		Size size();
		Mouse mouse();

		bool getKey(int key, int state = GLFW_PRESS);

		bool getMouseButton(int button, int state = GLFW_PRESS);

		void setMouseDisabled();
		void setMouseEnabled();

		bool isOpen();
		void close();

		void display();

		void setIcon(Image& image);

		operator GLFWwindow*();

	private:
		virtual void bindFramebuffer();
		void init();

		GLFWwindow* window = nullptr;
		void create(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	};
}