#include <memory>

import Sandcore.Scene.StateMachine;

namespace Sandcore {
	void SceneStateMachine::push(Scene* scene) {
		scenes.push(std::unique_ptr<Scene>(scene));
	}

	void SceneStateMachine::tick() {
		scenes.top()->tick();
	}

	bool SceneStateMachine::isEmpty() {
		return scenes.empty();
	}
}