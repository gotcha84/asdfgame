#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>


int main(int argc, char **argv) {
	
	// init glut
	glutInit(&argc, argv); // initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // open an OpenGL context with double buffering, RGB colors, and depth buffering
	glutInitWindowSize(400, 400); // set initial window size
	glutCreateWindow("asdfgame"); // open window and set window title
	
	// init glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	glutMainLoop();

	return 0;
}