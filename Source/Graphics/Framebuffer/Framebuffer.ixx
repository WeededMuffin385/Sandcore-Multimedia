#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


export module Sandcore.Graphics.Framebuffer;

import Sandcore.Graphics.Canvas;
import Sandcore.Graphics.Drawable;

import Sandcore.Graphics.Program;
import Sandcore.Graphics.Texture2D;
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
	private:
		void createFramebuffer();
		void createRenderbuffer(int width, int height);

		Size mSize;
		GLuint RBO = 0;
		Texture2D texture;
	};
}