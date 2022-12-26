#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Graphics.Draw.Target;

import Sandcore.Graphics.Draw.Object;

import Sandcore.Graphics.Texture;

import Sandcore.Shader.Program;

namespace Sandcore {
	void DrawTarget::draw(DrawObject& drawObject, ShaderProgram& shaderProgram, Texture& texture) {
		bindFramebuffer();
		shaderProgram.use();
		texture.bind();
		drawObject.draw();
	}

	void DrawTarget::clear(float red, float green, float blue, float alpha) {
		bindFramebuffer();
		glClearColor(red, green, blue, alpha); // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}