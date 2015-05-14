#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

#include "Named.h"

using namespace std;

class Model : public Named {
	private:
		bool m_dirty;

		GLuint m_vao;

		vector<float> m_vertices;
		GLuint m_vertexBuffer;

		vector<int> m_indices;
		GLuint m_indexBuffer;

		vector<float> m_colors;
		GLuint m_colorBuffer;
	
		void fillBuffers();

	public:
		Model(string name);
		~Model();

		virtual void draw();

		// getters
		vector<float> getVertices();
		vector<int> getIndices();
		vector<float> getColors();

		// setters
		void setVertices(float *vertices, int size);
		void setIndices(int *indices, int size);
		void setColors(float *colors, int size);
};

#endif