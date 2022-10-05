#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

import Sandcore.Camera;

import Sandcore.Window;
import Sandcore.Clock;

import Sandcore.Vector3D;
import Sandcore.Vector3D.GLM;

namespace Sandcore {
	Camera::Camera() {
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(position, position + front, up);
	}

	glm::mat4 Camera::getProjMatrix(int width, int height) {
		return glm::infinitePerspective(glm::radians(zoom), (double)width / (double)height, (double)0.1);
	}

	void Camera::updateVectors() {
		front.x = std::sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = std::cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.z = std::sin(glm::radians(pitch));

		front = glm::normalize(front);
		right = glm::normalize(glm::cross(worldUp, front));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = glm::normalize(glm::cross(front, right));
	}

	void Camera::mouseInput(Window& window) {
		if (first) {
			window.getMouse(&lastx, &lasty);
			first = false;
		}

		double posx;
		double posy;

		window.getMouse(&posx, &posy);

		double offsetx = posx - lastx;
		double offsety = lasty - posy;

		lastx = posx;
		lasty = posy;

		offsetx *= sensitivity;
		offsety *= sensitivity;

		yaw += offsetx;
		pitch += offsety;

		if (true)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateVectors();
	}

	Vector3D<double> Camera::getDirection(Window& window) {
		Vector3D<double> direction;

		if (window.getKey(GLFW_KEY_W)) direction += front;
		if (window.getKey(GLFW_KEY_S)) direction -= front;
		if (window.getKey(GLFW_KEY_A)) direction += right;
		if (window.getKey(GLFW_KEY_D)) direction -= right;

		return direction;
	}

	void Camera::keyboardInput(Window& window){
		static Clock clock;
		clock.restart();

		double velocity = speed * clock.getElapsedTime();

		if (window.getKey(GLFW_KEY_LEFT_SHIFT)) velocity *= 2;

		if (window.getKey(GLFW_KEY_W)) position += front * (float)velocity;
		if (window.getKey(GLFW_KEY_S)) position -= front * (float)velocity;
		if (window.getKey(GLFW_KEY_A)) position += right * (float)velocity;
		if (window.getKey(GLFW_KEY_D)) position -= right * (float)velocity;

		if (window.getKey(GLFW_KEY_SPACE)) position.z += velocity * 2;
		if (window.getKey(GLFW_KEY_LEFT_CONTROL)) position.z -= velocity;
	}

	void Camera::setFirst() {
		first = true;
	}
}