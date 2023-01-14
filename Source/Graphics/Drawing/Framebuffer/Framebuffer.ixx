#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


export module Sandcore.Framebuffer;

import Sandcore.Graphics.Draw.Target;
import Sandcore.Graphics.Draw.Object;

import Sandcore.Shader.Program;
import Sandcore.Graphics.Texture2D;
import Sandcore.Shader.Program;


export namespace Sandcore {
	class Framebuffer : public DrawTarget, public DrawObject {
	public:
		Framebuffer();

		void create(int width = 800, int height = 800);
		void resize(int width, int height);

		~Framebuffer();

		virtual void draw();

		GLuint& getRBO() { return RBO; };
		operator Texture2D&() { return texture; }

	private:
		virtual void bindFramebuffer();

		void createFramebuffer();
		void createRenderbuffer(int width, int height);

		GLuint FBO = 0;
		GLuint RBO = 0;
		Texture2D texture;
	};
}