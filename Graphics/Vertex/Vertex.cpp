#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Vertex;

namespace Sandcore {
	void Vertex::setAttributeDescriptions() {
		enum {stride = sizeof(Vertex)};

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
}