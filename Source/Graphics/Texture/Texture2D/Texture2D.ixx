#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

export module Sandcore.Graphics.Texture2D;

import Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture2D : public Texture {
	public:
		Texture2D();

		void create(int width, int height, const void* pixels = nullptr);
		void resize(int width, int height);

		void loadFromFile(std::filesystem::path path);

		Texture2D(const Texture2D& other) = delete;
		Texture2D& operator=(const Texture2D& other) = delete;

		Texture2D(Texture2D&& other);
		Texture2D& operator=(Texture2D&& other);
	};
}