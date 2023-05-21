#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

import Sandcore.Render.Camera;
import Sandcore.World.Bounds;
import Sandcore.World.Chunk;

namespace Sandcore {
	glm::f32vec3 RenderCamera::getDirection(Window& window) {
		glm::f32vec3 direction{};

		if (window.getKey(GLFW_KEY_W)) direction += front2D;
		if (window.getKey(GLFW_KEY_S)) direction -= front2D;
		if (window.getKey(GLFW_KEY_A)) direction += right2D;
		if (window.getKey(GLFW_KEY_D)) direction -= right2D;

		return direction;
	}

	void RenderCamera::updatePosition() {
		bound(worldPosition.x, position.x, WorldChunk::size::x);
		bound(worldPosition.y, position.y, WorldChunk::size::y);
		bound(worldPosition.z, position.z, WorldChunk::size::z);
	}

	void RenderCamera::mouseInput(Window& window) {
		Sandcore::Camera::mouseInput(window);
	}

	void RenderCamera::keyboardInput(Window& window) {
		Sandcore::Camera::keyboardInput(window);

		updatePosition();
	}

	void RenderCamera::updateVectors() {
		Sandcore::Camera::updateVectors();

		front2D.x = std::sin(glm::radians(yaw));
		front2D.y = std::cos(glm::radians(yaw));

		right2D = glm::normalize(glm::cross(worldUp, front));
	}

	void RenderCamera::setPosition(glm::i32vec3 worldPosition, glm::f32vec3 chunkPosition) {
		bounds<WorldChunk::size>(worldPosition, chunkPosition);

		this->worldPosition = worldPosition;

		position.x = chunkPosition.x;
		position.y = chunkPosition.y;
		position.z = chunkPosition.z;
	}
}