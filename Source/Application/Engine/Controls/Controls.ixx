module;
#include <string>
#include <glm/glm.hpp>
export module Sandcore.Controls;

import Sandcore.Window;
import Sandcore.Camera;

export namespace Sandcore {
	class Controls {
	public:
		void input(Window& window, Camera& camera);
		std::string generateMoveMessage();
		bool isChanged();

	private:

		glm::f32vec3 direction = { 0,0,0 };

		bool changed = false;
	};
}