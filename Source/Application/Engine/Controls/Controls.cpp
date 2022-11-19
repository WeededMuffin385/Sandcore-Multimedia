#include <string>
#include <GLFW/glfw3.h>


import Sandcore.Controls;

import Sandcore.Message;
import Sandcore.Window;
import Sandcore.Camera;

namespace Sandcore {
	void Controls::input(Window& window, Camera&camera) {
		Vector3D<double> direction = { 0,0,0 };
		MoveState moveState = MoveState::move;

		if (window.getKey(GLFW_KEY_LEFT_SHIFT))
			moveState = MoveState::run;

		if (window.getKey(GLFW_KEY_C))
			moveState = MoveState::sneak;

		direction = camera.getDirection(window);
		direction.z = static_cast<double>(static_cast<int>(window.getKey(GLFW_KEY_SPACE)) - static_cast<int>(window.getKey(GLFW_KEY_LEFT_ALT)));
	
		if ((this->direction != direction) || (this->moveState != moveState)) {
			this->direction = direction;
			this->moveState = moveState;
			changed = true;
		}
	}



	std::string Controls::generateMoveMessage() {
		changed = false;
		return Message::generateMoveMessage(direction, moveState);
	}

	bool Controls::isChanged() {
		return changed;
	}
}