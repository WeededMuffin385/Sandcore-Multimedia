#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

import Sandcore.Graphics.Canvas;
import Sandcore.Graphics.Drawable;

import Sandcore.Graphics.Texture;
import Sandcore.Shader.Program;

namespace Sandcore {
	void Canvas::draw(Drawable& object, ShaderProgram& shader, Texture& texture) {
		glViewport(0, 0, size.x, size.y);
		bindFramebuffer();
		shader.use();
		texture.bind();
		object.draw();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Canvas::draw(Drawable& object, ShaderProgram& shader) {
		glViewport(0, 0, size.x, size.y);
		bindFramebuffer();
		shader.use();
		object.draw();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Canvas::draw(Drawable& object) {
		glViewport(0, 0, size.x, size.y);
		bindFramebuffer();
		object.draw();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Canvas::clear(float red, float green, float blue, float alpha) {
		bindFramebuffer();
		glClearColor(red, green, blue, alpha); // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Canvas::viewport(int width, int height) {
		size.x = width;
		size.y = height;
	}
}