#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


export module Sandcore.Framebuffer;

import Sandcore.Graphics.Canvas;
import Sandcore.Graphics.Drawable;

import Sandcore.Shader.Program;
import Sandcore.Graphics.Texture2D;
import Sandcore.Shader.Program;
import Sandcore.Vertex;

export namespace Sandcore {
	using  FramebufferVertex = typename Vertex<glm::float32>;
	class Framebuffer : public Canvas, public Drawable {
	public:
		struct Size {
			int x;
			int y;
		};
	public:
		Framebuffer(int width = 800, int height = 800);

		void create(int width, int height);
		void resize(int width, int height);

		~Framebuffer();

		virtual void render();


		const Size& size() { return mSize; }
		GLuint& RBO() { return mRBO; };
		operator Texture2D&() { return texture; }

	private:
		virtual void bindFramebuffer();

		void createFramebuffer();
		void createRenderbuffer(int width, int height);

		Size mSize;
		GLuint mFBO = 0;
		GLuint mRBO = 0;
		Texture2D texture;
	};
}