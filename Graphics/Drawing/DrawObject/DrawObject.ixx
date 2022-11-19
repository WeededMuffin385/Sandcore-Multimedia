namespace Sandcore {
	class DrawTarget;
	class ShaderProgram;
}

export module Sandcore.Graphics.Draw.Object;

export namespace Sandcore {
	class DrawObject {
	private:
		virtual void draw() = 0;

		friend class DrawTarget;
	};
}