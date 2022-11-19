#include <stack>
#include <memory>

export module Sandcore.SceneStateMachine;

import Sandcore.Scene;

export namespace Sandcore {
	class SceneStateMachine {
	public:
		SceneStateMachine() {};

		void push(Scene* scene);

		void tick();

		bool isEmpty();

	private:
		std::stack<std::unique_ptr<Scene>> scenes;
	};
}