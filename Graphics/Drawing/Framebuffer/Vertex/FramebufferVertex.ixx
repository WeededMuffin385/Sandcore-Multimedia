#include <glm/glm.hpp>

export module Sandcore.Framebuffer.Vertex;

export namespace Sandcore {
	class FramebufferVertex {
	public:
		glm::float32 index;

		static void setAttributeDescriptions();
	};
}