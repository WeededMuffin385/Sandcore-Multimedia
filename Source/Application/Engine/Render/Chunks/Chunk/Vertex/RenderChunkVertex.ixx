#include <glm/glm.hpp>

export module Sandcore.Render.Chunk.Vertex;

import Sandcore.Vertex;

export  namespace Sandcore {
	using RenderChunkVertex = typename Vertex<glm::vec3, glm::float32, glm::float32, glm::float32>;
}