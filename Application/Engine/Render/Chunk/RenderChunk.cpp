#include <chrono>

import Sandcore.Render.Chunk;


namespace Sandcore {
	void RenderChunk::update() {
		for (auto& mesh : meshes) mesh.update();
		

		isLoaded = true;
	}

	void RenderChunk::setWanted() {
		wanted = std::chrono::high_resolution_clock::now();
	}

	bool RenderChunk::isUnwanted(std::chrono::high_resolution_clock::time_point& end) {
		return std::chrono::duration<double>(end - wanted).count() > wantedChunkTimeout;
	}

	RenderChunk::Identification RenderChunk::getIdentification(Block::Identification identification) {
		switch (identification) {
		case Block::Identification::leaves:
		case Block::Identification::water:
		case Block::Identification::vacuum:
			return RenderChunk::Identification::transparent;

		default:
			return RenderChunk::Identification::opaque;
		}
	}
}