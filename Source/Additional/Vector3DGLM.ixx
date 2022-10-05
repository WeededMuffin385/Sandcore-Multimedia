#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

export module Sandcore.Vector3D.GLM;

import Sandcore.Vector3D;

export namespace Sandcore {
	void operator+=(Vector3D<double>& left, const glm::vec3& right) {
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
	}

	void operator-=(Vector3D<double>& left, const glm::vec3& right) {
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
	}
}