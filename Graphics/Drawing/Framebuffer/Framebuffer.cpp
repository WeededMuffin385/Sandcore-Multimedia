#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

import Sandcore.Framebuffer;

import Sandcore.Mesh;

import Sandcore.Framebuffer.Vertex;
import Sandcore.Render.Chunk.Vertex;

namespace Sandcore {
	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &FBO);

		std::cout << "Framebuffer was deleted\n";
	}

	void Framebuffer::create(int width, int height) {
		createFramebuffer();

		texture.create(width, height);
		texture.bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.get(), 0);

		createRenderbuffer();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
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

	void Framebuffer::bindFramebuffer() {
		if (!FBO) std::cout << "FRAMEBUFFER WAS NOT CREATED!\n";

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);	
	}

	void Framebuffer::clear() {
		bindFramebuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Framebuffer::draw() {
		static Mesh<FramebufferVertex> mesh;
		static bool flag = true;
		if (flag) {
			mesh.vertices = { {0}, {1}, {2}, {3}, {4}, {5} };
			mesh.indices = { 0,1,2,3,4,5 };
			mesh.update();
			flag = false;
		}

		texture.bind();
		mesh.draw();
	}
}