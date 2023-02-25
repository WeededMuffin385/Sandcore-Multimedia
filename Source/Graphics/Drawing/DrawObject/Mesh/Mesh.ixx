#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

export module Sandcore.Mesh;

import Sandcore.Graphics.Draw.Object;

import Sandcore.Vertex;

export namespace Sandcore {
	template <class Vertex>
	class Mesh : public DrawObject {
	public:
		Mesh() {
		}

		~Mesh() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
		}

		virtual void draw() {
			if (vertices.empty()) return;
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}

		void update() {
			if (vertices.empty()) return;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

			Vertex::setAttributeDescriptions();

			glBindVertexArray(0);
		}

		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other) = delete;

		Mesh& operator=(const Mesh& other) = delete;
		Mesh& operator=(Mesh&& other) = delete;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	};
}