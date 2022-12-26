#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

export module Sandcore.Camera;

import Sandcore.Window;

import Sandcore.Vector3D;

export namespace Sandcore {
	class Camera {
	public:
		Camera();

		glm::mat4 getViewMatrix();
		glm::mat4 getProjMatrix(int width, int height);

		void setFirst();

		virtual Vector3D<double> getDirection(Window& window);
		glm::vec3 getFront();

		virtual void mouseInput(Window& window);
		virtual void keyboardInput(Window& window);

	protected:
		virtual void updateVectors();

		glm::vec3 position	= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 front		= glm::vec3(-1.0f, 0.0f, 0.0f);
		glm::vec3 up		= glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 right		= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 worldUp	= up;

		double yaw	= -90.0f;
		double pitch = 0.0f;

		double speed		= 25.f;
		double sensitivity	= 0.1f;
		double zoom			= 60.f;

		bool first = true;

		double lastx;
		double lasty;

	protected:

		friend class Frustum;
	};
}