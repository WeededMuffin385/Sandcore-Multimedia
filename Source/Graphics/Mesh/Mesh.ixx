#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

export module Sandcore.Mesh;

import Sandcore.Vertex;

export namespace Sandcore {
	template <typename VertexType>
	class Mesh {
	public:
		Mesh();
		~Mesh();

		void draw();
		void update();

		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other) = delete;

		Mesh& operator=(const Mesh& other) = delete;
		Mesh& operator=(Mesh&& other) = delete;

		std::vector<VertexType> vertices;
		std::vector<unsigned int> indices;

	private:

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	};
}