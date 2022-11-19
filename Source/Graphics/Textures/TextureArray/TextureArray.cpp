#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <iostream>

import Sandcore.TextureArray;

import Sandcore.Image;

namespace Sandcore {
	TextureArray::TextureArray(int width, int height, int layers) {
		create(width, height, layers);
	}

	TextureArray::TextureArray() {

	}

	void TextureArray::create(int width, int height, int layers) {
		this->width = width;
		this->height = height;
		glGenTextures(1, &textureArray);
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void TextureArray::generateMipmap() {
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void TextureArray::loadFromFile(int layer, std::filesystem::path path) {
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
		Image image(path);

		glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
						0,							// Mipmap number
						0, 0, layer,				// xoffset, yoffset, zoffset
						width, height, 1,			// width, height, depth
						GL_RGBA,					// format
						GL_UNSIGNED_BYTE,			// type
						image.data);				// pointer to data

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void TextureArray::bind() {
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	}
}