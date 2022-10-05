#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

import Sandcore.Framebuffer;


namespace Sandcore {
	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &FBO);

		std::cout << "Framebuffer was deleted\n";
	}

	void Framebuffer::create(int width, int height, GLuint* RBO) {
		createFramebuffer();

		texture.create(800, 600, nullptr);
		texture.bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.get(), 0);

		if (!RBO) createRenderbuffer(); else this->RBO = *RBO;
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RBO);

	
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::resize(int width, int height) {
		texture.resize(width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::createRenderbuffer() {
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::createFramebuffer() {
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
	}

	void Framebuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);	
	}

	void Framebuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::clear() {
		bind();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		unbind();
	}

	void Framebuffer::Vertex::setAttributeDescriptions() {
		int stride = sizeof(Vertex);

		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Framebuffer::bindTexture() {
		texture.bind();
	}

	void Framebuffer::unbindTexture() {
		texture.unbind();
	}
}