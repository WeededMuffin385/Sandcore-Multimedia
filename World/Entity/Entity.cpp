import Sandcore.World.Entity;

import Sandcore.World.Entity.Identification;

import Sandcore.Vector3D;

namespace Sandcore {
	Vector3D<int>& Entity::getWorldPosition() {
		return worldPosition;
	}

	Vector3D<double>& Entity::getChunkPosition() {
		return chunkPosition;
	}

	EntityIdentification& Entity::getId() {
		return identification;
	}

	Vector3D<double>& Entity::getSize() {
		return size;
	}
}