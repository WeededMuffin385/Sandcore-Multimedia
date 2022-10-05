#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <filesystem>

export module Sandcore.Image;

export namespace Sandcore {
	class Image {
	public:
		Image(std::filesystem::path path);
		~Image();

		void destroy();

		void loadFromFile(std::filesystem::path path);

		stbi_uc* data = nullptr;

		int width;
		int height;
		int channels;
	};
}