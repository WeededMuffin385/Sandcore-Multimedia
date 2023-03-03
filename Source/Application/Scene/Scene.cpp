import Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Application;

namespace Sandcore {
	Scene::Scene(Window& window, Event& event, Scenes& scenes) : window(window), event(event), scenes(scenes) {
		//Event::scene = this;
	}

	Scene::~Scene() {
		//if (Event::scene == this) Event::scene = nullptr;
	}

	void Scene::tick() {
		input();

		while (window.pollEvent(event)) {
			events();
		}

		update();
		draw();
	}

	void Scene::push(Scene* scene) {
		scenes.push(std::unique_ptr<Scene>(scene));
	}
}