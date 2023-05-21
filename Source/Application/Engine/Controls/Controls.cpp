#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
import Sandcore.Controls;

import Sandcore.Message;
import Sandcore.Window;
import Sandcore.Camera;

import Sandcore.Print;

namespace Sandcore {
	void Controls::input(Window& window, Camera&camera) {
		glm::f32vec3 direction = { 0,0,0 };

		direction = camera.getDirection(window);
		direction.z = static_cast<double>(static_cast<int>(window.getKey(GLFW_KEY_SPACE)) * 2 - static_cast<int>(window.getKey(GLFW_KEY_LEFT_ALT)));
	
		if (this->direction != direction) {
			this->direction = direction;
			changed = true;
		}
	}



	std::string Controls::generateMoveMessage() {
		changed = false;
		return Message::generateMoveMessage(direction);
	}

	bool Controls::isChanged() {
		return changed;
	}
}