module;
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
export module Sandcore.Render.Frustum;

import Sandcore.Camera;
import Sandcore.Vector3D;

export namespace Sandcore {
	class RenderFrustum {
	public:
		void update(Camera& camera, int width, int height){
			glm::mat4 matrix = glm::inverse(camera.getProjViewMatrix(width, height));

			frustum_planes[0] = matrix[3] + matrix[0];
			// Right plane
			frustum_planes[1] = matrix[3] - matrix[0];
			// Bottom plane
			frustum_planes[2] = matrix[3] + matrix[1];
			// Top plane
			frustum_planes[3] = matrix[3] - matrix[1];
			// Near plane
			frustum_planes[4] = matrix[3] + matrix[2];
			// Far plane
			frustum_planes[5] = matrix[3] - matrix[2];

			glm::normalize(frustum_planes[0]);
			glm::normalize(frustum_planes[1]);
			glm::normalize(frustum_planes[2]);
			glm::normalize(frustum_planes[3]);
			glm::normalize(frustum_planes[4]);
			glm::normalize(frustum_planes[5]);

			/*
			for (auto& plane : frustum_planes) {
				plane = glm::normalize(plane);
			}
			*/
		}

		/*
		bool isInside(const glm::vec3& min, const glm::vec3& max) {
			glm::vec3 vertices[8] = {
				glm::vec3(min.x, min.y, min.z),
				glm::vec3(max.x, min.y, min.z),
				glm::vec3(min.x, max.y, min.z),
				glm::vec3(max.x, max.y, min.z),
				glm::vec3(min.x, min.y, max.z),
				glm::vec3(max.x, min.y, max.z),
				glm::vec3(min.x, max.y, max.z),
				glm::vec3(max.x, max.y, max.z)
			};

			// Test each vertex against all six planes
			for (const auto& plane : frustum_planes) {
				bool inside = false;
				for (const auto& vertex : vertices) {
					if (glm::dot(plane, glm::vec4(vertex, 1.0f)) >= 0.0f) {
						inside = true;
						break;
					}
				}
				if (!inside) {
					return false;
				}
			}

			return true;
		}
		*/

		bool isChunkInside(Vector3D<int> position) {
			glm::vec3 min = glm::vec3(position.x, position.y, position.z) * 16.0f; // assuming chunks are 16x16x16
			glm::vec3 max = min + glm::vec3(16.0f, 16.0f, 16.0f);
			// Test the chunk against the frustum planes
			return true;
			//return isInside(min, max);
		}

	private:
		glm::vec4 frustum_planes[6];
	};
}