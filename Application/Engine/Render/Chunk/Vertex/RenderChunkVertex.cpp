#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Render.Chunk.Vertex;

namespace Sandcore {
	void RenderChunkVertex::setAttributeDescriptions() {
		enum { stride = sizeof(RenderChunkVertex) };

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, stride, (void*)(12));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, stride, (void*)(16));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, stride, (void*)(20));
		glEnableVertexAttribArray(3);
	}
}