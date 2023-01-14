namespace Sandcore {
	class DrawObject;
	class ShaderProgram;
}

export module Sandcore.Graphics.Draw.Target;

import Sandcore.Graphics.Texture;
import Sandcore.Sprite;

export namespace Sandcore {
	class DrawTarget {
	public:
		virtual void draw(DrawObject& drawObject, ShaderProgram& shaderProgram, Texture& texture) final;
		virtual void draw(Sprite& sprite) final;
		virtual void clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 0.0f) final;

	protected:
		virtual void bindFramebuffer() = 0;
	};
}