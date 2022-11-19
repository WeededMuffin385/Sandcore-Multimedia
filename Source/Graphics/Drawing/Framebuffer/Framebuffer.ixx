#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


export module Sandcore.Framebuffer;

import Sandcore.Graphics.Draw.Target;
import Sandcore.Graphics.Draw.Object;

import Sandcore.Shader.Program;
import Sandcore.Texture;
import Sandcore.Mesh;


export namespace Sandcore {
	class Framebuffer : public DrawTarget, public DrawObject {
	public:
		void create(int width = 800, int height = 600);
		void resize(int width, int height);

		~Framebuffer();

		virtual void bindFramebuffer();
		virtual void draw();

		void clear();

		GLuint& getRBO() { return RBO; };

	private:
		void createFramebuffer();
		void createRenderbuffer();

		GLuint FBO = 0;
		GLuint RBO = 0;
		Texture texture;
	};
}