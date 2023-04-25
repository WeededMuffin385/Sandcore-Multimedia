module;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
export module Sandcore.Graphics.Texture2D;

import Sandcore.Graphics.Texture;
import Sandcore.Image;

export namespace Sandcore {
	class Texture2D : public Texture {
	public:
		Texture2D() : Texture(GL_TEXTURE_2D) {
		}

		void resize(int width, int height) {
			this->width = width;
			this->height = height;
			create();
			glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
		}

		void loadFromFile(std::filesystem::path path) {
			Image image(path);
			width = image.getSize().x;
			height = image.getSize().y;
			resize(width, height);
			glTextureSubImage2D(
				texture,
				0,
				0, 0,
				width, height,
				GL_RGBA, GL_UNSIGNED_BYTE,
				image.getData()
			);
		}
	private:
		int width, height;
	};
}