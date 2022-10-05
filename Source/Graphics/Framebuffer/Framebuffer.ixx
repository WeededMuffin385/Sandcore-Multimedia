#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

import Sandcore.Texture;

export module Sandcore.Framebuffer;

export namespace Sandcore {
	class Framebuffer {
	public:
		class Vertex {
		public:
			glm::float32 index;

			static void setAttributeDescriptions();
		};
		
		void create(int width, int height, GLuint*RBO);
		void resize(int width, int height);

		void createFramebuffer();
		void createRenderbuffer();

		~Framebuffer();

		void bind();
		void unbind();

		void bindTexture();
		void unbindTexture();

		void clear();


		GLuint& getRBO() { return RBO; };

	private:

		GLuint FBO = 0;
		GLuint RBO = 0;
		Texture texture;
	};
}