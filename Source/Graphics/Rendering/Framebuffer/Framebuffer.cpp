#include <filesystem>
#include <glm/glm.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Framebuffer;
import Sandcore.Print;

import Sandcore.Graphics.Mesh;
import Sandcore.Shader.Program;

import Sandcore.Vertex;
import Sandcore.Application.Memory;

namespace Sandcore {
	Framebuffer::Framebuffer(int width, int height) {
		create(width, height);
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &mFBO);
	}

	void Framebuffer::create(int width, int height) {
		mSize.x = width;
		mSize.y = height;
		texture.create(width, height);

		createFramebuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		createRenderbuffer(width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);
	}

	void Framebuffer::resize(int width, int height) {
		mSize.x = width;
		mSize.y = height;
		texture.resize(width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::createFramebuffer() {
		glGenFramebuffers(1, &mFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		}
	}

	void Framebuffer::createRenderbuffer(int width, int height) {
		glGenRenderbuffers(1, &mRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::bindFramebuffer() {
		if (!mFBO) std::print("ERROR: FRAMEBUFFER DOESN'T EXISTS");

		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);	
	}

	void Framebuffer::render() {
		static Mesh<Vertex<glm::float32>> frame;
		static ShaderProgram shader(Memory::shaderScreenPath);
		static bool first = true;
		if (first) [[unlikely]]{
			frame.vertices = { {0}, {1}, {2}, {3} };
			frame.indices = { 0, 1, 2, 0, 2, 3 };
			frame.update();
			first = false;
		}
		shader.use();
		texture.bind();
		frame.render();
	}
}