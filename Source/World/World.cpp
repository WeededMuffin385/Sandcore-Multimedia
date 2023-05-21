#include <list>
#include <chrono>
#include <glm/glm.hpp>
import Sandcore.World;
import Sandcore.World.Chunk;

namespace Sandcore {
	void World::tick() {
		std::list<glm::i32vec3> unwantedChunks;

		auto now = std::chrono::high_resolution_clock::now();

		for (auto& [position, chunk] : chunks) {
			if (chunk.isUnwanted(now)) unwantedChunks.push_back(position);
		}

		for (auto& position : unwantedChunks) {
			chunks.erase(position);
		}
	}

	WorldChunk& World::getChunk(int x, int y, int z) {
		return getChunk(glm::i32vec3(x, y, z));
	}

	WorldChunk& World::getChunk(glm::i32vec3 position) {
		return chunks[position];
	}

	std::unordered_map<int, std::unique_ptr<Entity>>& World::getEntities() {
		return entities;
	}
}