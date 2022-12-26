#include <stb/stb_image.h>
#include <filesystem>



import Sandcore.Image;

namespace Sandcore {
	Image::Image(std::filesystem::path path) {
		loadFromFile(path);
	}

	Image::~Image() {
		destroy();
	}

	void Image::destroy() {
		if (data != nullptr) stbi_image_free(data);
	}

	void Image::loadFromFile(std::filesystem::path path) {
		destroy();
		data = stbi_load(path.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (data == nullptr) {
		}
	}
}