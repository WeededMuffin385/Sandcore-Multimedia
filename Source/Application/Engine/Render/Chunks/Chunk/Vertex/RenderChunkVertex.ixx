#include <glm/glm.hpp>

export module Sandcore.Render.Chunk.Vertex;

export  namespace Sandcore {
	class RenderChunkVertex {
	public:
		glm::vec3 pos;
		glm::float32 shade;
		glm::float32 texId;
		glm::float32 index;

		static void setAttributeDescriptions();
	};
}