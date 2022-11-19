export module Sandcore.Interface.Rectangle;

import Sandcore.Vector2D;

export namespace Sandcore {
	class Rectangle {
	public:
		Rectangle(Vector2D<double> size, Vector2D<double> position);
		Rectangle(double width, double height, double x, double y);

		bool isColliding(Vector2D<double> mouse);

	private:
		Vector2D<double> size;
		Vector2D<double> position;
	};
}