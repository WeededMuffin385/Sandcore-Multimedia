#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

export module Sandcore.Shader.Object;

export namespace Sandcore {
	class ShaderObject {
	public:
		ShaderObject(GLenum type);
		~ShaderObject();

		void loadFromFile(std::filesystem::path path);
		operator GLuint();
	private:
		GLuint shaderObject;
	};
}