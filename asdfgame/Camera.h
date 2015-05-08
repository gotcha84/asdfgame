#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {

	private:
		// window
		GLFWwindow *m_window;
		int m_windowWidth, m_windowHeight;

		// coordinates
		glm::vec3 m_center;
		glm::vec3 m_lookAt;
		
		// unit-vector directions
		glm::vec3 m_up;
		glm::vec3 m_right;

		glm::mat4 m_viewMatrix;
		
		float m_horizontalAngle;
		float m_verticalAngle;
		float m_moveSpeed;
		float m_mouseSpeed;

		// methods
		void printDebugInfo();
		void getWindowDimensions();
		void centerMouse();

	public:
		Camera(GLFWwindow *window);
		~Camera();
		void initVars();

		void updateCamera(double prevTime);
		void updateCameraRotation();
		void updateCameraMovement(double prevTime);
		void updateViewMatrix();

		// setters
		glm::vec3 getCenter();
		glm::vec3 getLookAt();
		glm::vec3 getUp();
		glm::vec3 getRight();
		glm::mat4 getViewMatrix();

		// getters
		void setCenter(glm::vec3 center);
		void setLookAt(glm::vec3 lookAt);
		void setUp(glm::vec3 up);
		void setRight(glm::vec3 right);
		void setViewMatrix(glm::mat4 viewMatrix);

};

#endif