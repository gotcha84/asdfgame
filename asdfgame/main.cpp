#define DEBUG_FPS 0

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "SceneGraph.h"

using namespace std;

GLFWwindow* window;
GLuint vertexArrayID;

int init() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "asdfgame", nullptr, nullptr);
	if (window == nullptr){
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n%s\n", glewGetErrorString(glewInitResult));
		return -1;
	}

	return 0;
}

void cleanup() {

	// Cleanup VBO
	glDeleteVertexArrays(1, &vertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

int main(int argc, char *argv[]) {

	// init
	int initResult = init();
	if (initResult != 0) {
		return initResult;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key being pressed below

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background

	// GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static float vertex_data[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	static int index_data[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//static float vertex_data[] = {
	//	-1.0f, -1.0f, -1.0f, // triangle 1 : begin
	//	-1.0f, -1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	//	1.0f, 1.0f, -1.0f, // triangle 2 : begin
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, 1.0f, -1.0f, // triangle 2 : end
	//	1.0f, -1.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, 1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, -1.0f,
	//	1.0f, -1.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f,
	//	-1.0f, -1.0f, -1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, 1.0f, -1.0f,
	//	1.0f, -1.0f, -1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, -1.0f,
	//	-1.0f, 1.0f, -1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, -1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	1.0f, -1.0f, 1.0f
	//};

	//GLuint vertexbuffer;
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	//GLuint programID = Shader::loadShaders("simple.vert", "simple.frag");

	sg::BasicGeode node("cube");
	node.setVertices(vertex_data, sizeof(vertex_data) / sizeof(float));
	node.setIndices(index_data, sizeof(index_data) / sizeof(float));

	Camera camera(window);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	double prevFrameTime = glfwGetTime();
	double prevTimeFPS = prevFrameTime;
	double numFramesFPS = 0;

	while (!glfwWindowShouldClose(window)) {

		double currTime = glfwGetTime();

		numFramesFPS++;
		if (currTime - prevTimeFPS >= 1.0){ // If last prinf() was more than 1 sec ago
			// print and reset timer
			if (DEBUG_FPS) {
				fprintf(stderr, "%f ms (< %f ms)\n", (currTime - prevTimeFPS) * 1000.0f / double(numFramesFPS), 1000.0f / 60.0f);
			}
			numFramesFPS = 0;
			prevTimeFPS = currTime;
		}

		camera.updateCamera(prevFrameTime);
		// glm::mat4 MVP = getProjMatrix() * camera.getViewMatrix() * modelMatrix;

		// TODO graphics stuff

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		//// Use our shader
		//glUseProgram(programID);

		//// Get a handle for our "MVP" uniform.
		//// Only at initialisation time.
		//GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		//// Send our transformation to the currently bound shader,
		//// in the "MVP" uniform
		//// For each model you render, since the MVP will be different (at least the M part)
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		//// 1rst attribute buffer : vertices
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glVertexAttribPointer(
		//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		//	3,                  // size
		//	GL_FLOAT,           // type
		//	GL_FALSE,           // normalized?
		//	0,                  // stride
		//	(void*)0            // array buffer offset
		//	);

		//// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 12*3); // 3 indices starting at 0 -> 1 triangle

		//glDisableVertexAttribArray(0);

		// anurag
		node.draw(modelMatrix, camera.getViewMatrix());

		// if esc key is pressed, close the window
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		prevFrameTime = currTime;
	}

	// cleanup
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteProgram(programID);
	cleanup();

	return 0;
}
