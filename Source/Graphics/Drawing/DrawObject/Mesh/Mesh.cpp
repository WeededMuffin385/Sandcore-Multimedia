#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Mesh;

import Sandcore.Vertex;
import Sandcore.Framebuffer.Vertex;
import Sandcore.Render.Chunk.Vertex;

import Sandcore.Graphics.Draw.Target;

namespace Sandcore {
	template class Mesh<Vertex>;
	template class Mesh<RenderChunkVertex>;
	template class Mesh<FramebufferVertex>;

	template <typename VertexType>
	Mesh<VertexType>::Mesh() {

	}

	template <typename VertexType>
	Mesh<VertexType>::~Mesh() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	template <typename VertexType>
	void Mesh<VertexType>::draw() {
		if (vertices.empty()) return;

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	template <typename VertexType>
	void Mesh<VertexType>::update(){
		if (vertices.empty()) return;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		VertexType::setAttributeDescriptions();

		glBindVertexArray(0);
	}
}