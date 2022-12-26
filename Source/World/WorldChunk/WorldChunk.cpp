#include <string>
#include <memory>

import Sandcore.World.Chunk;

namespace Sandcore {
	WorldChunk::WorldChunk() {
	}

	const Block& WorldChunk::getBlock(Vector3D<int> position) {
		return getBlock(position.x, position.y, position.z);
	}

	const Block& WorldChunk::getBlock(int x, int y, int z) {
		return blocks[x][y][z];
	}

	void WorldChunk::setBlock(Vector3D<int> position, Block block) {
		setBlock(position.x, position.y, position.z, block);
	}

	void WorldChunk::setBlock(int x, int y, int z, Block block) {
		blocks[x][y][z] = block;
		changed = true;
	}

	void WorldChunk::upload(std::string& data) {
		std::memcpy(&blocks[0][0][0], data.data(), x * y * z * sizeof(Block));
	}
}