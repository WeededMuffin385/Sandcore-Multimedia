module;
#include <glm/glm.hpp>
#include <chrono>
export module Sandcore.Render.Chunk;

import Sandcore.Graphics.Mesh;
import Sandcore.Vertex;
import Sandcore.World.Chunk;
import Sandcore.World.Block;


export namespace Sandcore {
	using RenderChunkVertex = typename Vertex<glm::vec3, glm::float32, glm::float32, glm::float32>;

	class RenderChunk {
	public:
		enum Identification {
			opaque,
			transparent,
			leaves,
			size
		};
		static Identification getIdentification(Block::Identification identification);

		void clear();
		void update();

		void setWanted();
		bool isUnwanted(std::chrono::high_resolution_clock::time_point& end);

		bool loaded = false;

		Mesh<RenderChunkVertex> meshes[size];

		std::chrono::high_resolution_clock::time_point wanted = std::chrono::high_resolution_clock::now();
	};
}