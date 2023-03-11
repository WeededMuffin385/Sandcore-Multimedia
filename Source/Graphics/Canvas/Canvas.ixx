namespace Sandcore {
	class Drawable;
	class Program;
}

export module Sandcore.Graphics.Canvas;

import Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Canvas {
	public:
		virtual void draw(Drawable& object, Program& shader, Texture& texture) final;
		virtual void draw(Drawable& object, Program& shader) final;
		virtual void draw(Drawable& object) final;
		virtual void clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 0.0f) final;
		virtual void viewport(int width, int height) final;
	protected:
		struct Size {
			int x;
			int y;
		};

		Size size;

		virtual void bindFramebuffer() = 0;
	};
}