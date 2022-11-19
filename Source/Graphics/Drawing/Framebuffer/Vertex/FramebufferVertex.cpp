#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Framebuffer.Vertex;

namespace Sandcore {
	void FramebufferVertex::setAttributeDescriptions() {
		int stride = sizeof(FramebufferVertex);

		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);
	}
}