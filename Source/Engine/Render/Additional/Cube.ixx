export module Sandcore.Cube;

export namespace Sandcore {
	struct Axis {
		float minus;
		float plus;
	};

	struct Cube {
		Axis x;
		Axis y;
		Axis z;
	};
}