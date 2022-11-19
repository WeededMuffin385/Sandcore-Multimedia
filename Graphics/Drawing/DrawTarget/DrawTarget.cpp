import Sandcore.Graphics.Draw.Target;

import Sandcore.Graphics.Draw.Object;

import Sandcore.Shader.Program;

namespace Sandcore {
	void DrawTarget::draw(DrawObject& drawObject, ShaderProgram& shaderProgram) {
		bindFramebuffer();
		shaderProgram.use();
		drawObject.draw();
	}
}