
#include <memory>
import Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Application;

namespace Sandcore {
	Scene::Scene(Window& window, Event& event, Scenes& scenes) : window(window), event(event), scenes(scenes) {
	}

	Scene::~Scene() {
	}

	void Scene::tick() {
		input();

		while (window.pollEvent(event)) {
			events();
		}

		update();
		draw();
	}

	void Scene::push(std::shared_ptr<Scene> scene) {
		scenes.push(std::move(scene));
	}

	void Scene::push(Scene* scene) {
		scenes.push(std::shared_ptr<Scene>(scene));
	}
}