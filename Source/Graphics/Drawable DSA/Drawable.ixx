export module Sandcore.Graphics.Drawable;

export namespace Sandcore {
	class Drawable {
	protected:
		virtual void render() = 0;
		friend class Canvas;
	};
}