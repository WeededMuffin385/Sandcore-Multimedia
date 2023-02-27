#include <chrono>

import Sandcore.Render.Chunk;


namespace Sandcore {
	void RenderChunk::update() {
		for (auto& mesh : meshes) mesh.update();
		
		loaded = true;
	}

	void RenderChunk::clear() {
		for (auto& mesh : meshes) {
			mesh.indices.clear();
			mesh.vertices.clear();
		}
	}

	void RenderChunk::setWanted() {
		wanted = std::chrono::high_resolution_clock::now();
	}

	bool RenderChunk::isUnwanted(std::chrono::high_resolution_clock::time_point& end) {
		const double wantedChunkTimeout = 10;
		return std::chrono::duration<double>(end - wanted).count() > wantedChunkTimeout;
	}

	RenderChunk::Identification RenderChunk::getIdentification(Block::Identification identification) {
		switch (identification) {
		case Block::Identification::Leaves:
			return RenderChunk::Identification::leaves;
		case Block::Identification::Water:
		case Block::Identification::Vacuum:
			return RenderChunk::Identification::transparent;

		default:
			return RenderChunk::Identification::opaque;
		}
	}
}