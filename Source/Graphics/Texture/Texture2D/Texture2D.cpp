#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>


import Sandcore.Graphics.Texture2D;

import Sandcore.Graphics.Texture;

import Sandcore.Image;

namespace Sandcore {
	Texture2D::Texture2D() {
		type = GL_TEXTURE_2D;
	}

	void Texture2D::create(int width, int height, const void* pixels) {
		glGenTextures(1, &texture);
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		unbind();
	}

	void Texture2D::resize(int width, int height) {
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		unbind();
	}

	void Texture2D::loadFromFile(std::filesystem::path path) {
		Image image(path);

		create(image.size().x, image.size().y, image.data());
	}

	Texture2D::Texture2D(Texture2D&& other) {
		texture = other.texture;
		type = other.type;

		other.texture = 0;
	}

	Texture2D& Texture2D::operator=(Texture2D&& other)  {
		if (this != &other) {
			release();

			std::swap(texture, other.texture);
		}
		return *this;
	}
}