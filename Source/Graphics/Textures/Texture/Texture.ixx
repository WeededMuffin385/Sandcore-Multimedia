#define GLEW_STATIC
#include <GL/glew.h>

export module Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture {
	public:

		Texture();
		~Texture();

		virtual void bind() final;
		virtual void unbind() final;

		virtual operator GLuint() final;

	protected:
		virtual void release() final;

		GLuint texture = 0;
		int type = 0;
	};
}