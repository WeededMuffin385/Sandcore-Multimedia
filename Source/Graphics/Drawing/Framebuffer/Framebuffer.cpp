#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Framebuffer;
import Sandcore.Render.Chunk.Vertex;
import Sandcore.Print;

namespace Sandcore {
	Framebuffer::Framebuffer() {
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &FBO);
	}

	void Framebuffer::create(int width, int height) {
		texture.create(width, height);

		createFramebuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		createRenderbuffer(width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
	}

	void Framebuffer::resize(int width, int height) {
		texture.resize(width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::createFramebuffer() {
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		}
	}

	void Framebuffer::createRenderbuffer(int width, int height) {
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::bindFramebuffer() {
		if (!FBO) std::print("ERROR: FRAMEBUFFER DOESN'T EXISTS");

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);	
	}

	void Framebuffer::draw() {
		texture.bind();
	}
}