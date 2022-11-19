#include <chrono>

export module Sandcore.Render.Chunk;

import Sandcore.Mesh;
import Sandcore.Render.Chunk.Vertex;

import Sandcore.World.Block;

export namespace Sandcore {
	class RenderChunk {
	public:
		enum Identification {
			opaque,
			transparent,
			size
		};
		static Identification getIdentification(Block::Identification identification);


		void update();

		void setWanted();
		bool isUnwanted(std::chrono::high_resolution_clock::time_point& end);

		bool isLoaded = false;

		Mesh<RenderChunkVertex> meshes[size];

		std::chrono::high_resolution_clock::time_point wanted = std::chrono::high_resolution_clock::now();
		enum { wantedChunkTimeout = 10 };
	};
}