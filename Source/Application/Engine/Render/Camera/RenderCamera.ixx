#include <glm/glm.hpp>

export module Sandcore.Render.Camera;

import Sandcore.Camera;

export namespace Sandcore {
	class RenderCamera : public Camera {
	public:
		glm::i32vec3 getWorldPosition() { return worldPosition; }
		glm::f32vec3 getChunkPosition() { return glm::f32vec3(position.x, position.y, position.z); }

		void setPosition(glm::i32vec3 worldPosition, glm::f32vec3 chunkPosition);
		void updatePosition();

		virtual glm::f32vec3 getDirection(Window& window);

		virtual void mouseInput(Window& window);
		virtual void keyboardInput(Window& window);

	private:
		virtual void updateVectors();

		glm::i32vec3 worldPosition;

		glm::vec3 front2D;
		glm::vec3 right2D;
	};
}