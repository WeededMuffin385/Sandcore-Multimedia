#include <string>
#include <memory>
#include <chrono>
#include <glm/glm.hpp>
import Sandcore.World.Chunk;

namespace Sandcore {
	WorldChunk::WorldChunk() {
	}

	const Block& WorldChunk::getBlock(glm::i32vec3 position) {
		return getBlock(position.x, position.y, position.z);
	}

	const Block& WorldChunk::getBlock(int x, int y, int z) {
		return blocks[x][y][z];
	}

	void WorldChunk::setBlock(glm::i32vec3 position, Block block) {
		setBlock(position.x, position.y, position.z, block);
	}

	void WorldChunk::setBlock(int x, int y, int z, Block block) {
		blocks[x][y][z] = block;
		changed = true;
	}

	void WorldChunk::upload(std::string& data) {
		std::memcpy(blocks, data.data(), x * y * z * sizeof(Block));
	}

	bool WorldChunk::isUnwanted(std::chrono::high_resolution_clock::time_point& end) {
		const double wantedChunkTimeout = 10;
		return std::chrono::duration<double>(end - wanted).count() > wantedChunkTimeout;
	}

	void WorldChunk::setWanted() {
		wanted = std::chrono::high_resolution_clock::now();
	}
}