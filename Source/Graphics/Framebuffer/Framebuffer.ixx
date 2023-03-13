#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>

#include <glm/glm.hpp>
export module Sandcore.Graphics.Framebuffer;

import Sandcore.Graphics.Canvas;
import Sandcore.Graphics.Drawable;

import Sandcore.Graphics.Texture2D;
import Sandcore.Vertex;

import Sandcore.Graphics.Mesh;
import Sandcore.Graphics.Program;

import Sandcore.Application.Memory;
import Sandcore.Vector2D;

export namespace Sandcore {
	class Framebuffer : public Canvas, public Drawable {
	public:
		Framebuffer() {
			glCreateFramebuffers(1, &FBO);
		}

		~Framebuffer() {
			glDeleteTextures(1, &color);
			glDeleteTextures(1, &depth);
			glDeleteFramebuffers(1, &FBO);
		}

		void toggle() {
			magnification = magnification == GL_NEAREST ? GL_LINEAR : GL_NEAREST;
			glTextureParameteri(color, GL_TEXTURE_MAG_FILTER, magnification);
		}

		void resize(int width, int height) {
			return resize({ width, height });
		}

		void resize(Vector2D<int> size) {
			if (this->size == size) return;
			this->size = size;

			glDeleteTextures(1, &color);
			glDeleteTextures(1, &depth);

			glCreateTextures(GL_TEXTURE_2D, 1, &color);
			glCreateTextures(GL_TEXTURE_2D, 1, &depth);

			glTextureParameteri(color, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(color, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(color, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(color, GL_TEXTURE_MAG_FILTER, magnification);

			glTextureStorage2D(color, 1, GL_RGBA8, size.x, size.y);
			glTextureStorage2D(depth, 1, GL_DEPTH_COMPONENT24, size.x, size.y);

			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);
		}

		virtual void render() {
			static Mesh<Vertex<glm::float32>> frame;
			static Program shader(Memory::shaderScreenPath);
			static bool init = []()->bool {
				frame.vertices = { {0}, {1}, {2}, {3} };
				frame.indices = { 0, 1, 2, 0, 2, 3 };
				frame.update();
				return true;
			}();

			shader.use();
			glBindTextureUnit(0, color);
			frame.render();
		}

		virtual Vector2D<int> getSize() {
			return size;
		}

	private:
		Vector2D<int> size;
		GLenum magnification = GL_NEAREST;

		GLuint depth;
		GLuint color;
	};
}