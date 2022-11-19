export module Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Event;

export namespace Sandcore {
	class Scene {
	public:
		Scene(Window& window, Event& event);

		virtual void tick() = 0;

		Window& window;
		Event& event;
	};
}