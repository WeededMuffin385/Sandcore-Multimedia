#include <glm/glm.hpp>

export module Sandcore.Render.Camera;

import Sandcore.Camera;

export namespace Sandcore {
	class RenderCamera : public Camera {
	public:
		Vector3D<int> getWorldPosition() { return worldPosition; }
		Vector3D<double> getChunkPosition() { return Vector3D<double>(position.x, position.y, position.z); }

		void setPosition(Vector3D<int> worldPosition, Vector3D<double> chunkPosition);

		virtual Vector3D<double> getDirection(Window& window);

		virtual void mouseInput(Window& window);
		virtual void keyboardInput(Window& window);

	private:
		virtual void updateVectors();

		Vector3D<int> worldPosition;

		glm::vec3 front2D;
		glm::vec3 right2D;
	};
}