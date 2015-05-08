#define DEBUG_CENTER 0

#include <iostream>

#include "Camera.h"
#include "Constants.h"

Camera::Camera() {
	setCenter(glm::vec3(0, 0, 5));
	setLookAt(glm::vec3(0, 0, 4));
	
	setUp(glm::vec3(0, 1, 0));
	setRight(glm::vec3(1, 0, 0));

	m_moveSpeed = 3.0f; // 3 units/sec
	m_mouseSpeed = 0.0005f;

	m_horizontalAngle = 0;
	m_verticalAngle = 0;

	updateViewMatrix();
}

Camera::~Camera() {

}

void Camera::updateCamera(GLFWwindow *window, double prevTime) {
	updateCameraRotation(window);
	updateCameraMovement(window, prevTime);
	updateViewMatrix();
}

void Camera::updateCameraRotation(GLFWwindow *window) {
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos); // get current mouse position

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight); // get current window size
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2); // reset mouse position

	m_horizontalAngle += float(windowWidth / 2 - xPos) * m_mouseSpeed;
	m_verticalAngle += float(windowHeight / 2 - yPos) * m_mouseSpeed;

	glm::vec3 oldLookIn = getLookAt() - getCenter();
	glm::vec3 lookInHorizontal = glm::vec3(sin(m_horizontalAngle), oldLookIn.y, cos(m_horizontalAngle));
	glm::vec3 lookInVertical = glm::vec3(oldLookIn.x * cos(m_verticalAngle), sin(m_verticalAngle), oldLookIn.z * cos(m_verticalAngle));
	glm::vec3 newLookIn = glm::normalize(lookInHorizontal + lookInVertical);
	
	setLookAt(getCenter() + newLookIn);

	float rightHorizontalAngle = m_horizontalAngle - PI / 2.0f;
	setRight(glm::vec3(sin(rightHorizontalAngle), getRight().y, cos(rightHorizontalAngle)));

	setUp(glm::normalize(glm::cross(getRight(), newLookIn)));
}

void Camera::updateCameraMovement(GLFWwindow *window, double prevTime) {
	double currTime = glfwGetTime();
	float deltaTime = float(currTime - prevTime);

	glm::vec3 position = getCenter();
	glm::vec3 lookIn = getLookAt() - getCenter();
	glm::vec3 forward = glm::vec3(lookIn.x, 0, lookIn.z);

	bool moved = false;

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		position += forward * deltaTime * m_moveSpeed;
		moved = true;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		position -= forward * deltaTime * m_moveSpeed;
		moved = true;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		position += getRight() * deltaTime * m_moveSpeed;
		moved = true;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		position -= getRight() * deltaTime * m_moveSpeed;
		moved = true;
	}

	setCenter(position);
	setLookAt(getCenter() + lookIn);

	if (DEBUG_CENTER) {
		if (moved) {
			fprintf(stderr, "camera center: %s\n", glm::to_string(getCenter()).c_str());
		}
	}
}

void Camera::updateViewMatrix() {
	setViewMatrix(glm::lookAt(getCenter(), getLookAt(), getUp()));
}


// getters
glm::vec3 Camera::getCenter() {
	return m_center;
}

glm::vec3 Camera::getLookAt() {
	return m_lookAt;
}

glm::vec3 Camera::getUp() {
	return m_up;
}

glm::vec3 Camera::getRight() {
	return m_right;
}

glm::mat4 Camera::getViewMatrix() {
	updateViewMatrix();
	return m_viewMatrix;
}


// setters
void Camera::setCenter(glm::vec3 center) {
	m_center = center;
}

void Camera::setLookAt(glm::vec3 lookAt) {
	m_lookAt = lookAt;
}

void Camera::setUp(glm::vec3 up) {
	m_up = up;
}

void Camera::setRight(glm::vec3 right) {
	m_right = right;
}

void Camera::setViewMatrix(glm::mat4 viewMatrix) {
	m_viewMatrix = viewMatrix;
}
