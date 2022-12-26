#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

export module Sandcore.Vector3D.GLM;

import Sandcore.Vector3D;

export namespace Sandcore {
	Vector3D<double> translate(glm::vec3& vector) {
		return Vector3D<double>(vector.x, vector.y, vector.z);
	}

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