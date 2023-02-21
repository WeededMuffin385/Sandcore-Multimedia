#include <glm/glm.hpp>

export module Sandcore.Framebuffer.Vertex;

import Sandcore.Vertex;

export namespace Sandcore {
	using  FramebufferVertex = typename Vertex<glm::float32>;
}