#include <string>
#include <memory>

import Sandcore.World;

namespace Sandcore {
	World::Chunk::Chunk() {
	}

	World::Chunk::Block& World::Chunk::getBlock(Vector3D<int> position) {
		return getBlock(position.x, position.y, position.z);
	}

	World::Chunk::Block& World::Chunk::getBlock(int x, int y, int z) {
		return blocks[x][y][z];
	}

	void World::Chunk::setBlock(Vector3D<int> position, Block block) {
		setBlock(position.x, position.y, position.z, block);
	}

	void World::Chunk::setBlock(int x, int y, int z, Block block) {
		blocks[x][y][z] = block;
	}

	void World::Chunk::upload(std::string& data) {
		std::memcpy(&blocks[0][0][0], data.data(), x * y * z * sizeof(Block));
	}
}