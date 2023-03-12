module;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
export module Sandcore.Graphics.Canvas;

import Sandcore.Graphics.Drawable;
import Sandcore.Graphics.Texture;
import Sandcore.Graphics.Program;

export namespace Sandcore {
	class Canvas {
	public:
		virtual void clear(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f) final {
			color[0] = r;
			color[1] = g;
			color[2] = b;
			color[3] = a;
			glClearNamedFramebufferfv(FBO, GL_COLOR, 0, color);
			glClearNamedFramebufferfv(FBO, GL_DEPTH, 0, &depth);
		}

		virtual void bind() final {
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		}

		virtual void draw(Drawable& drawable, Program& program, Texture& texture) {
			bind();
			program.use();
			texture.bind();
			drawable.render();
		}

		virtual void draw(Drawable& drawable, Program& program) {
			bind();
			program.use();
			drawable.render();
		}

		virtual void draw(Drawable& drawable) {
			bind();
			drawable.render();
		}

		virtual void viewport(int width, int height) {
			glViewport(0, 0, width, height);
		}

	protected:
		GLuint FBO = 0;
		GLfloat color[4] = { 0.f, 0.5f, 0.f, 0.f };
		GLfloat depth = 1.0f;
	};
}