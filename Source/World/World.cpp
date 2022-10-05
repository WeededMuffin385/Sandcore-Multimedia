import Sandcore.World;

import Sandcore.Vector3D;

namespace Sandcore {
	World::Chunk& World::getChunk(int x, int y, int z) {
		return getChunk(Vector3D<int>(x, y, z));
	}

	World::Chunk& World::getChunk(Vector3D<int> position) {
		return chunks[position];
	}

	std::unordered_map<Vector3D<int>, World::Chunk, Vector3DHash<int>>& World::getChunks() {
		return chunks;
	}

	std::unordered_map<int, std::unique_ptr<Entity>>& World::getEntities() {
		return entities;
	}
}