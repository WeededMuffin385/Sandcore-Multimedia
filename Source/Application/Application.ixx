#include <queue>
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
		void push(Scene* scene);
	private:
		Window window;
		Event event;

		std::queue<std::unique_ptr<Scene>> scenes;
	};
}