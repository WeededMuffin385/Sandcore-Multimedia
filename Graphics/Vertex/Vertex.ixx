#include <glm/glm.hpp>

export module Sandcore.Vertex;

export namespace Sandcore {
	class Vertex {
	public:
		glm::vec3 pos;
		glm::vec3 color;

		static void setAttributeDescriptions();
	};
}