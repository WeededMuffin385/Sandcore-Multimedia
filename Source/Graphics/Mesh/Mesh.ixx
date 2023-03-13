#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <vector>
export module Sandcore.Graphics.Mesh;

import Sandcore.Graphics.Drawable;

import Sandcore.Print;

export namespace Sandcore {
	template <typename Vertex, typename Index = std::uint32_t>
	class Mesh : public Drawable {
	public:
		Mesh() {
			glCreateVertexArrays(1, &VAO);
			Vertex::setAttributeDescriptions(VAO);
		}

		~Mesh() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteVertexArrays(1, &VAO);
		}


		virtual void render() {
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}

		void update() {
			if ((vertices.size() > vboSize) || (indices.size() > eboSize)) {
				resize();
				subdata();
			} else if (created && (vertices.size() <= vboSize) && (indices.size() <= eboSize)) subdata();

			// std::print("{} OF {} VERTICES | {} OF {} INDICES\n", vertices.size(), vboSize, indices.size(), eboSize);
		}

		std::vector<Vertex> vertices;
		std::vector<Index> indices;
	private:
		void resize() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			
			glCreateBuffers(1, &VBO);
			glCreateBuffers(1, &EBO);

			glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Vertex));
			glVertexArrayElementBuffer(VAO, EBO);

			glNamedBufferStorage(VBO, sizeof(Vertex) * vertices.size(), NULL, GL_DYNAMIC_STORAGE_BIT);
			glNamedBufferStorage(EBO, sizeof(Index) * indices.size(), NULL, GL_DYNAMIC_STORAGE_BIT);

			vboSize = vertices.size();
			eboSize = indices.size();
			created = true;
		}

		void subdata (){
			glNamedBufferSubData(VBO, 0, sizeof(Vertex) * vertices.size(), vertices.data());
			glNamedBufferSubData(EBO, 0, sizeof(Index) * indices.size(), indices.data());
		}

		bool created = false;
		int vboSize = 0;
		int eboSize = 0;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	};
}