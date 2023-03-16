#include <stack>
#include <memory>

export module Sandcore.Application;

import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Scene;

export namespace Sandcore {
	class Application {
	public:
		Application();

		void loop();
		void tick();
		void push(Scene* scene);

	private:
		inline static Application* application = nullptr;
		static void foo();

		Scenes scenes;
		Window window;
		Event event;
	};
}