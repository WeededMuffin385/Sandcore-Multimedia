#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>


import Sandcore.Graphics.Texture3D;

import Sandcore.Image;

namespace Sandcore {
	Texture3D::Texture3D() {
		type = GL_TEXTURE_2D_ARRAY;
	}

	void Texture3D::create(int width, int height, int layers) {
		this->width = width;
		this->height = height;
		glGenTextures(1, &texture);

		bind();
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		unbind();
	}

	void Texture3D::generateMipmap() {
		bind();
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		unbind();
	}

	void Texture3D::loadFromFile(int layer, std::filesystem::path path) {
		Image image(path);

		bind();
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
						0,							// Mipmap number
						0, 0, layer,				// xoffset, yoffset, zoffset
						width, height, 1,			// width, height, depth
						GL_RGBA,					// format
						GL_UNSIGNED_BYTE,			// type
						image.data());				// pointer to data
		unbind();
	}
}