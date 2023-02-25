namespace Sandcore {
	class DrawObject;
	class ShaderProgram;
}

export module Sandcore.Graphics.Draw.Target;

import Sandcore.Graphics.Texture;

export namespace Sandcore {
	class DrawTarget {
	public:
		virtual void draw(DrawObject& object, ShaderProgram& shader, Texture& texture) final;
		virtual void draw(DrawObject& object, ShaderProgram& shader) final;
		virtual void clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 0.0f) final;

	protected:
		virtual void bindFramebuffer() = 0;
	};
}