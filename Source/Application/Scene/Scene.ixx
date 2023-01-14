export module Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Event;

export namespace Sandcore {
	class Scene {
	public:
		Scene(Window& window, Event& event);

		virtual void tick() final;
		virtual void render() final;
	protected:
		virtual void draw() = 0;
		virtual void input() = 0;
		virtual void update() = 0;
		virtual void events() = 0;

		Window& window;
		Event& event;
	};
}