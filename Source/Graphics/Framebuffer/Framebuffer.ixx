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

export namespace Sandcore {
	class Framebuffer : public Canvas, public Drawable {
	public:
		Framebuffer(int width = 800, int height = 800) {
			glCreateFramebuffers(1, &FBO);
		}

		~Framebuffer() {
			glDeleteFramebuffers(1, &FBO);
		}

		void resize(int width, int height) {
			glDeleteTextures(1, &COLOR);
			glDeleteTextures(1, &DEPTH);

			glCreateTextures(GL_TEXTURE_2D, 1, &COLOR);
			glCreateTextures(GL_TEXTURE_2D, 1, &DEPTH);

			glTextureParameteri(COLOR, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(COLOR, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(COLOR, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(COLOR, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureStorage2D(COLOR, 1, GL_RGBA8, width, height);
			glTextureStorage2D(DEPTH, 1, GL_DEPTH_COMPONENT24, width, height);

			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, COLOR, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DEPTH, 0);
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
			glBindTextureUnit(0, COLOR);
			frame.render();
		}
	private:
		GLuint DEPTH;
		GLuint COLOR;
	};
}