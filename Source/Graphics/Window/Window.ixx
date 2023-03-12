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

		enum Cursor {
			Disabled = GLFW_CURSOR_DISABLED,
			Normal = GLFW_CURSOR_NORMAL,
		};
	public:
		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~Window();

		bool pollEvent(Event& event);
		bool isOpen();

		void display();

		Size size();
		Mouse mouse();

		void setContext();
		void toggleCursor(Cursor mode);

		bool getKey(int key, int state = GLFW_PRESS);
		bool getMouseButton(int button, int state = GLFW_PRESS);

		void setIcon(Image& image);
	private:
		GLFWwindow* window = nullptr;
	};
}