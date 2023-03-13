#include <queue>
#include <unordered_map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

export module Sandcore.Event;

export namespace Sandcore {
	class Event {
	public:
		enum class Type {
			Cursor,
			Mouse,
			Key,
			Window
		};

		Type type;

		union {
			struct {
				double x;
				double y;
			} cursor;

			struct {
				int button;
				int action;
				int mode;
			} mouse;

			struct {
				int key;
				int scancode;
				int action;
				int mode;
			} key;

			struct {
				int width;
				int height;
			} window;
		};

	private:
		friend class Window;
		static bool pollEvent(GLFWwindow* window, Event& event);
		static void setCurrentWindow(GLFWwindow* window);

		static void setWindowCallback(GLFWwindow* window);

		static std::unordered_map<GLFWwindow*, std::queue<Event>> events;

		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void window_size_callback(GLFWwindow* window, int width, int height);
	};
}