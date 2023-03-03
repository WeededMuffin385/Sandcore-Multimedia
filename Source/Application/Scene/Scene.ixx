module;
#include <stack>
#include <memory>
export module Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Event;

export namespace Sandcore {
	class Scene {
	public:
		using Scenes = std::stack<std::unique_ptr<Scene>>;
		Scene(Window& window, Event& event, Scenes&scenes);
		~Scene();

		virtual void tick() final;
	protected:
		virtual void draw() = 0;
		virtual void input() = 0;
		virtual void events() = 0;
		virtual void update() = 0;

		void push(Scene* scene);

		Scenes& scenes;
		Window& window;
		Event& event;
	};
}