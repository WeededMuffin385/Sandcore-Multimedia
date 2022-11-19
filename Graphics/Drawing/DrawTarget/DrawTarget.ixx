namespace Sandcore {
	class DrawObject;
	class ShaderProgram;
}

export module Sandcore.Graphics.Draw.Target;

export namespace Sandcore {
	class DrawTarget {
	public:
		virtual void draw(DrawObject& drawObject, ShaderProgram& shaderProgram) final;

		virtual void bindFramebuffer() = 0;
	};
}