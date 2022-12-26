import Sandcore.Scene;

import Sandcore.Window;
import Sandcore.Event;

namespace Sandcore {
	Scene::Scene(Window& window, Event& event) : window(window), event(event) {

	}

	void Scene::tick() {
		input();

		while (window.pollEvent(event)) {
			events();
		}

		update();
		draw();
	}
}