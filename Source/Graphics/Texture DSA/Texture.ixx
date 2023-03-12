module;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
export module Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture {
	public:
		Texture(GLenum target) : target(target){
		}

		void create() {
			glDeleteTextures(1, &texture);
			glCreateTextures(target, 1, &texture);

			glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		void generateMipmap() {
			glGenerateTextureMipmap(texture);
		}

		void bind() {
			glBindTextureUnit(0, texture);
		}

		virtual ~Texture() {
			glDeleteTextures(1, &texture);
		}

		operator GLuint() {
			return texture;
		}
	protected:
		GLenum target;
		GLuint texture;
	};
}