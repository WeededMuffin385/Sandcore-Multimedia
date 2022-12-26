import Sandcore.World.Entity;

import Sandcore.Vector3D;

namespace Sandcore {
	Vector3D<int>& Entity::getWorldPosition() {
		return worldPosition;
	}

	Vector3D<double>& Entity::getChunkPosition() {
		return chunkPosition;
	}

	Entity::Identification& Entity::getId() {
		return identification;
	}

	Vector3D<double>& Entity::getSize() {
		return size;
	}
}