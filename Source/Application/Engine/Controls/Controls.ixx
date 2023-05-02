module;
#include <string>
export module Sandcore.Controls;

import Sandcore.Vector3D;
import Sandcore.Window;
import Sandcore.Camera;

export namespace Sandcore {
	class Controls {
	public:
		void input(Window& window, Camera& camera);
		std::string generateMoveMessage();
		bool isChanged();

	private:

		Vector3D<double> direction = { 0,0,0 };

		bool changed = false;
	};
}