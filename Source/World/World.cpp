#include <list>
#include <chrono>

import Sandcore.World;

import Sandcore.Vector3D;
import Sandcore.World.Chunk;

namespace Sandcore {
	void World::tick() {
		std::list<Vector3D<int>> unwantedChunks;

		auto now = std::chrono::high_resolution_clock::now();

		for (auto& [position, chunk] : chunks) {
			if (chunk.isUnwanted(now)) unwantedChunks.push_back(position);
		}

		for (auto& position : unwantedChunks) {
			chunks.erase(position);
		}
	}

	WorldChunk& World::getChunk(int x, int y, int z) {
		return getChunk(Vector3D<int>(x, y, z));
	}

	WorldChunk& World::getChunk(Vector3D<int> position) {
		return chunks[position];
	}

	std::unordered_map<int, std::unique_ptr<Entity>>& World::getEntities() {
		return entities;
	}
}