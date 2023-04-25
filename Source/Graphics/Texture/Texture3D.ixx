module;
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
export module Sandcore.Graphics.Texture3D;

import Sandcore.Graphics.Texture;
import Sandcore.Image;

export namespace Sandcore {
	class Texture3D : public Texture {
	public:
		Texture3D() : Texture(GL_TEXTURE_2D_ARRAY) {
		}

		void resize(int width, int height, int depth) {
			this->width = width;
			this->height = height;
			this->depth = depth;
			create();
			glTextureStorage3D(texture, 7, GL_RGBA8, width, height, depth);
		}

		void loadFromFile(int layer, std::filesystem::path path) {
			Image image(path);

			glTextureSubImage3D(
				texture,
				0,
				0, 0, layer,
				width, height, 1,
				GL_RGBA, GL_UNSIGNED_BYTE,
				image.getData()
			);
		}
	private:
		int width, height, depth;
	};
}