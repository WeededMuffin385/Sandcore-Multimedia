#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Interface.Vertex;


namespace Sandcore {
	void InterfaceVertex::setAttributeDescriptions() {
		enum { stride = sizeof(InterfaceVertex) };

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
}