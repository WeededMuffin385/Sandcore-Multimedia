module;
#include <stack>
#include <memory>
export module Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Event;

export namespace Sandcore {
	class Scene;
	using Scenes = std::stack<std::shared_ptr<Scene>>;

	class Scene {
	public:
		Scene(Window& window, Event& event, Scenes&scenes);
		virtual ~Scene();

		virtual void tick() final;
	protected:
		virtual void draw() = 0;
		virtual void input() = 0;
		virtual void events() = 0;
		virtual void update() = 0;

		void push(std::shared_ptr<Scene> scene);
		void push(Scene* scene);
		bool run = true;

		Window& window;
		Event& event;
		Scenes& scenes;
	private:
		friend class Application;
	};
}