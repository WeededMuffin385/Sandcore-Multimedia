#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

import Sandcore.Render;

import Sandcore.World.Bounds;
import Sandcore.World;

import Sandcore.Vector3D;
import Sandcore.Vector3D.GLM;

namespace Sandcore {
	Vector3D<double> Render::Camera::getDirection(Window& window) {
		Vector3D<double> direction;

		if (window.getKey(GLFW_KEY_W)) direction += front2D;
		if (window.getKey(GLFW_KEY_S)) direction -= front2D;
		if (window.getKey(GLFW_KEY_A)) direction += right2D;
		if (window.getKey(GLFW_KEY_D)) direction -= right2D;

		return direction;
	}

	void Render::Camera::mouseInput(Window& window) {
		Sandcore::Camera::mouseInput(window);
	}

	void Render::Camera::keyboardInput(Window& window) {
		Sandcore::Camera::keyboardInput(window);

		bound(worldPosition.x, position.x, World::Chunk::size::x);
		bound(worldPosition.y, position.y, World::Chunk::size::y);
		bound(worldPosition.z, position.z, World::Chunk::size::z);
	}

	void Render::Camera::updateVectors() {
		Sandcore::Camera::updateVectors();

		front2D.x = std::sin(glm::radians(yaw));
		front2D.y = std::cos(glm::radians(yaw));

		right2D = glm::normalize(glm::cross(worldUp, front));
	}
}