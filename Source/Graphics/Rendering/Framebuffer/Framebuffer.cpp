#include <filesystem>
#include <glm/glm.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Framebuffer;
import Sandcore.Print;

import Sandcore.Mesh;
import Sandcore.Shader.Program;

import Sandcore.Vertex;

namespace Sandcore {
	Framebuffer::Framebuffer(int width, int height) {
		create(width, height);
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
		static Mesh<Vertex<glm::float32>> frame;
		static ShaderProgram shader("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/Shaders/ScreenShaders");
		static bool first = true;
		if (first) [[unlikely]]{
			frame.vertices = { {0}, {1}, {2}, {3} };
			frame.indices = { 0, 1, 2, 0, 2, 3 };
			frame.update();
			first = false;
		}
		shader.use();
		texture.bind();
		frame.draw();
	}
}