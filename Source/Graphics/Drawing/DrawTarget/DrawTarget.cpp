#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

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
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void DrawTarget::draw(Sprite& sprite) {
		static ShaderProgram screenShader("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/shaders/screen_shader");


		bindFramebuffer();
		screenShader.use();
		sprite.draw();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void DrawTarget::clear(float red, float green, float blue, float alpha) {
		bindFramebuffer();
		glClearColor(red, green, blue, alpha); // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}