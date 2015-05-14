#ifndef RENDERABLEGO_H
#define RENDERABLEGO_H

#include <GL/glew.h>

#include "GameObject.h"

#include <vector>


class RenderableGO : public GameObject {
	private:
		glm::mat4 m_modelMatrix;

		GLuint m_shaderProgramId;

		GLuint m_vao;
		bool m_dirty;

		vector<float> m_vertices;
		GLuint m_vertexBuffer;
		bool m_vertexBufferExists;

		vector<int> m_indices;
		GLuint m_indexBuffer;
		bool m_indexBufferExists;

		vector<float> m_colors;
		GLuint m_colorBuffer;
		bool m_colorBufferExists;

	public:
		RenderableGO(string name);
		~RenderableGO();

		void fillBuffers();
		virtual void draw(glm::mat4 parent, glm::mat4 viewMatrix);

		virtual ostream& print(ostream &stream);

		// getters
		glm::mat4 getModelMatrix();
		vector<float> getVertices();
		vector<int> getIndices();
		vector<float> getColors();

		// setters
		void setModelMatrix(glm::mat4 modelMatrix);
		void setVertices(float *vertices, int size);
		void setIndices(int *indices, int size);
		void setColors(float *colors, int size);
};

#endif