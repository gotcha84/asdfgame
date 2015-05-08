#define DEBUG_CAMERA 0

#include <iostream>

#include "Camera.h"
#include "Constants.h"

/*
	private methods
*/

void Camera::printDebugInfo() {
	fprintf(stderr, "%s, %s\n", glm::to_string(getCenter()).c_str(), glm::to_string(getLookAt()).c_str());
}

void Camera::getWindowDimensions() {
	glfwGetWindowSize(m_window, &m_windowWidth, &m_windowHeight); // get current window size
}

void Camera::centerMouse() {
	glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2); // reset mouse position
}

/*
	public methods
*/

Camera::Camera(GLFWwindow *window) {
	m_window = window;
	getWindowDimensions();
	centerMouse();

	initVars();

	setCenter(glm::vec3(0, 0, 5));
	setLookAt(glm::vec3(0, 0, 4));
	setUp(glm::vec3(0, 1, 0));
	setRight(glm::vec3(1, 0, 0));
	updateViewMatrix();
}

Camera::~Camera() {

}

void Camera::initVars() {
	m_moveSpeed = 3.0f; // 3 units/sec
	m_mouseSpeed = 0.0005f;

	// causes sudden camera swivel on init if wrong value
	// TODO bug will reappear if initial lookIn (lookAt - center) changes
	m_horizontalAngle = PI;
	m_verticalAngle = 0;
}

void Camera::updateCamera(double prevTime) {
	updateCameraRotation();
	updateCameraMovement(prevTime);
	updateViewMatrix();
}

void Camera::updateCameraRotation() {

	double xPos, yPos;
	glfwGetCursorPos(m_window, &xPos, &yPos); // get current mouse position
	
	// if mouse still in window center, no need to recalculate view matrix
	if (xPos == m_windowWidth / 2 && yPos == m_windowHeight / 2) {
		return;
	}
	centerMouse();

	m_horizontalAngle += float(m_windowWidth / 2 - xPos) * m_mouseSpeed;
	m_verticalAngle += float(m_windowHeight / 2 - yPos) * m_mouseSpeed;

	glm::vec3 oldLookIn = getLookAt() - getCenter();
	glm::vec3 lookInHorizontal = glm::vec3(sin(m_horizontalAngle), oldLookIn.y, cos(m_horizontalAngle));
	glm::vec3 lookInVertical = glm::vec3(oldLookIn.x * cos(m_verticalAngle), sin(m_verticalAngle), oldLookIn.z * cos(m_verticalAngle));
	glm::vec3 newLookIn = glm::normalize(lookInHorizontal + lookInVertical);
	
	setLookAt(getCenter() + newLookIn);

	float rightHorizontalAngle = m_horizontalAngle - PI / 2.0f;
	setRight(glm::vec3(sin(rightHorizontalAngle), getRight().y, cos(rightHorizontalAngle)));

	setUp(glm::normalize(glm::cross(getRight(), newLookIn)));
}

void Camera::updateCameraMovement(double prevTime) {
	double currTime = glfwGetTime();
	float deltaTime = float(currTime - prevTime);

	glm::vec3 position = getCenter();
	glm::vec3 lookIn = getLookAt() - getCenter();
	glm::vec3 forward = glm::vec3(lookIn.x, 0, lookIn.z);

	bool moved = false;

	// Move forward
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS){
		position += forward * deltaTime * m_moveSpeed;
		moved = true;
	}
	// Move backward
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS){
		position -= forward * deltaTime * m_moveSpeed;
		moved = true;
	}
	// Strafe right
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS){
		position += getRight() * deltaTime * m_moveSpeed;
		moved = true;
	}
	// Strafe left
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS){
		position -= getRight() * deltaTime * m_moveSpeed;
		moved = true;
	}

	setCenter(position);
	setLookAt(getCenter() + lookIn);
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
