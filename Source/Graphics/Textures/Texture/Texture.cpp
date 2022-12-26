#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Graphics.Texture;

namespace Sandcore {
	Texture::Texture() {

	}

	Texture::~Texture() {
		release();
	}

	void Texture::bind() {
		glBindTexture(type, texture);
	}

	void Texture::unbind() {
		glBindTexture(type, 0);
	}

	void Texture::release() {
		glDeleteTextures(1, &texture);
	}

	Texture::operator GLuint() {
		return texture;
	}
}