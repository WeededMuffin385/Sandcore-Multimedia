#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

export module Sandcore.TextureArray;

export namespace Sandcore {
	class TextureArray {
	public:

		TextureArray(int width, int height, int layers);
		TextureArray();

		void create(int width, int height, int layers);

		void loadFromFile(int layer, std::filesystem::path path);

		void generateMipmap();

		void bind();

	private:
		int width;
		int height;
		GLuint textureArray;
	};
}