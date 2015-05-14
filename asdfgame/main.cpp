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
#include "GameObjects.h"

using namespace std;

GLFWwindow* window;

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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static float vertex_data[] = {
		-1.0f, -1.0f, 0.0f,		// bottom-left
		0.0f, -1.0f, 1.0f,		// bottom-back
		1.0f, -1.0f, 0.0f,		// bottom-right
		0.0f, 1.0f, 0.0f		// top
	};

	static float vertex_data2[] = {
		-4.0f, -1.0f, 0.0f,		// bottom-left
		-3.0f, -1.0f, 1.0f,		// bottom-back
		-2.0f, -1.0f, 0.0f,		// bottom-right
		-3.0f, 1.0f, 0.0f		// top
	};

	static float color_data[] = {
		1.0f, 0.0f, 0.0f,		// red
		0.0f, 1.0f, 0.0f,		// green
		0.0f, 0.0f, 1.0f,		// blue
		1.0f, 1.0f, 1.0f		// white
	};

	static int index_data[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	RenderableGO node("cube1");
	node.setVertices(vertex_data, sizeof(vertex_data) / sizeof(vertex_data[0]));
	node.setIndices(index_data, sizeof(index_data) / sizeof(index_data[0]));
	node.setColors(color_data, sizeof(color_data) / sizeof(color_data[0]));

	RenderableGO node2("cube2");
	node2.setVertices(vertex_data2, sizeof(vertex_data2) / sizeof(vertex_data2[0]));
	node2.setIndices(index_data, sizeof(index_data) / sizeof(index_data[0]));
	node2.setColors(color_data, sizeof(color_data) / sizeof(color_data[0]));

	Camera camera(window);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	double prevFrameTime = glfwGetTime();
	double prevTimeFPS = prevFrameTime;
	double numFramesFPS = 0;

	while (!glfwWindowShouldClose(window)) {

		double currTime = glfwGetTime();

		numFramesFPS++;
		if (currTime - prevTimeFPS >= 1.0){ // if last prinf() was more than 1 sec ago
			// print and reset timer
			if (DEBUG_FPS) {
				fprintf(stderr, "%f ms (< %f ms)\n", (currTime - prevTimeFPS) * 1000.0f / double(numFramesFPS), 1000.0f / 60.0f);
			}
			numFramesFPS = 0;
			prevTimeFPS = currTime;
		}

		camera.updateCamera(prevFrameTime);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw
		node.draw(modelMatrix, camera.getViewMatrix());
		node2.draw(modelMatrix, camera.getViewMatrix());

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
	cleanup();

	return 0;
}
