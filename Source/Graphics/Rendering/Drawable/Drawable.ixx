namespace Sandcore {
	class Canvas;
	class ShaderProgram;
}

export module Sandcore.Graphics.Drawable;

export namespace Sandcore {
	class Drawable {
	public:
		virtual void render() = 0;

		friend class Canvas;
	};
}