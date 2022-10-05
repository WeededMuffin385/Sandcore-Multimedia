#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <iostream>

import Sandcore.Texture;

import Sandcore.Image;

namespace Sandcore {
	void Texture::create(int width, int height, const void*pixels) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::resize(int width, int height) {
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		unbind();
	}

	GLuint Texture::get() {
		return texture;
	}

	void Texture::loadFromFile(std::filesystem::path path) {
		Image image(path);

		create(image.width, image.height, image.data);
	}

	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture() {
		release();
	}


	Texture::Texture(Texture&& other) : texture(other.texture) {
		other.texture = 0;
	}

	Texture& Texture::operator=(Texture&& other)  {
		if (this != &other) {
			release();

			std::swap(texture, other.texture);
		}
		return *this;
	}

	void Texture::release() {
		glDeleteTextures(1, &texture);
	}
}