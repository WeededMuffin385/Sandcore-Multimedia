#include <glm/glm.hpp>

import Sandcore.World.Entity;

namespace Sandcore {
	glm::i32vec3& Entity::getWorldPosition() {
		return worldPosition;
	}

	glm::f32vec3& Entity::getChunkPosition() {
		return chunkPosition;
	}

	Entity::Identification& Entity::getId() {
		return identification;
	}

	glm::f32vec3& Entity::getSize() {
		return size;
	}
}