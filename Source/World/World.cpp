import Sandcore.World;

import Sandcore.Vector3D;
import Sandcore.World.Chunk;

namespace Sandcore {
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