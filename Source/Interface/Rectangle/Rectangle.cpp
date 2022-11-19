import Sandcore.Interface.Rectangle;

import Sandcore.Vector2D;

namespace Sandcore {
	Rectangle::Rectangle(Vector2D<double> size, Vector2D<double> position) : size(size), position(position) {

	}

	Rectangle::Rectangle(double width, double height, double x, double y) : size(width, height), position(x, y) {
	
	}

	bool Rectangle::isColliding(Vector2D<double> mouse) {
		bool a = mouse.x >= position.x;
		bool b = mouse.y >= position.y;

		bool c = mouse.x <= (position.x + size.x);
		bool d = mouse.y <= (position.y + size.y);

		return a && b && c && d;
	}
}