#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

export module Sandcore.Graphics.Texture3D;

import Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture3D : public Texture {
	public:
		Texture3D();

		void create(int width, int height, int layers);

		void loadFromFile(int layer, std::filesystem::path path);

		void generateMipmap();

	private:
		int width;
		int height;
	};
}