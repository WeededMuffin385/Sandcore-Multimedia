#include <glm/glm.hpp>

export module Sandcore.Interface.Vertex;

export namespace Sandcore {
	class InterfaceVertex {
	public:
		glm::vec2 pos;
		glm::vec2 tex;

		static void setAttributeDescriptions();
	};
}