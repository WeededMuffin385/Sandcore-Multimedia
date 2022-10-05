#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

export module Sandcore.Shader;

export namespace Sandcore {
	class Shader {
	public:

		Shader(GLenum type);
		~Shader();

		void loadFromFile(std::filesystem::path path);
		GLuint get();

	private:

		GLuint shader;
	};
}