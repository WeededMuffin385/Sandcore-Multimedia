export module Sandcore.Application;

import Sandcore.SceneStateMachine;
import Sandcore.Window;
import Sandcore.Event;

export namespace Sandcore {
	class Application {
	public:
		Application();

		void loop();

	private:
		Window window;
		Event event;

		SceneStateMachine scenes;
	};
}