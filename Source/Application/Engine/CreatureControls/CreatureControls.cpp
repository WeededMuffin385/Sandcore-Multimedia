#include <string>
#include <GLFW/glfw3.h>

import Sandcore.Creature.Controls;

import Sandcore.Message;
import Sandcore.Window;
import Sandcore.Camera;

namespace Sandcore {
	void CreatureControls::input(Window& window, Camera&camera) {
		Vector3D<double> direction = { 0,0,0 };

		direction = camera.getDirection(window);
		direction.z = static_cast<double>(static_cast<int>(window.getKey(GLFW_KEY_SPACE)) * 2 - static_cast<int>(window.getKey(GLFW_KEY_LEFT_ALT)));
	
		if (this->direction != direction) {
			this->direction = direction;
			changed = true;
		}
	}



	std::string CreatureControls::generateMoveMessage() {
		changed = false;
		return Message::generateMoveMessage(direction);
	}

	bool CreatureControls::isChanged() {
		return changed;
	}
}