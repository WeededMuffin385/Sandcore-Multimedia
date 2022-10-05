#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>

export module Sandcore.Texture;

export namespace Sandcore {
	class Texture {
	public:
		Texture() {};
		~Texture();

		GLuint get();

		void create(int width, int height, const void* pixels);
		void resize(int width, int height);

		void loadFromFile(std::filesystem::path path);

		void bind();
		void unbind();


		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;

		Texture(Texture&& other);
		Texture& operator=(Texture&& other);

	private:

		void release();

		GLuint texture = 0;
	};
}