#include "BasicGeode.h"

#include "Shader.h"

namespace sg {

	BasicGeode::BasicGeode(string name) : Geode(name) {
		m_shaderProgramId = Shader::loadShaders("simple.vert", "simple.frag");
		m_vboExists = false;
		m_iboExists = false;
	}

	BasicGeode::~BasicGeode() {
		glDeleteProgram(m_shaderProgramId);

		if (m_vboExists) {
			glDeleteBuffers(1, &m_vbo);
		}

		if (m_iboExists) {
			glDeleteBuffers(1, &m_ibo);
		}
	}

	void BasicGeode::draw(glm::mat4 parent, glm::mat4 viewMatrix) {
		glm::mat4 modelMatrix = parent * getModelMatrix();
		glm::mat4 mvpMatrix = getProjMatrix() * viewMatrix * modelMatrix;

		// Use our shader
		glUseProgram(m_shaderProgramId);
		GLuint mvpMatrixId = glGetUniformLocation(m_shaderProgramId, "mvpMatrix");
		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);

		glEnableVertexAttribArray(0);

		//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//glVertexAttribPointer(
		//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		//	3,                  // size
		//	GL_FLOAT,           // type
		//	GL_FALSE,           // normalized?
		//	0,                  // stride
		//	(void*)0            // array buffer offset
		//	);

		// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 3 indices starting at 0 -> 1 triangle

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glDrawElements(GL_TRIANGLES, getIndices().size(), GL_UNSIGNED_INT, (void *)0);

		glDisableVertexAttribArray(0);
	}

	// getters
	vector<float> BasicGeode::getVertices() {
		return m_vertices;
	}

	vector<int> BasicGeode::getIndices() {
		return m_indices;
	}

	// setters
	void BasicGeode::setVertices(vector<float> vertices) {
		m_vertices = vertices;
	}

	void BasicGeode::setVertices(float *vertices, int size) {
		if (m_vboExists) {
			glDeleteBuffers(1, &m_vbo);
		}

		m_vertices = vector<float>(vertices, vertices + size);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, getVertices().size() * sizeof(float), getVertices().data(), GL_STATIC_DRAW);

		m_vboExists = true;
	}

	void BasicGeode::setIndices(vector<int> indices) {
		m_indices = indices;
	}

	void BasicGeode::setIndices(int *indices, int size) {
		if (m_iboExists) {
			glDeleteBuffers(1, &m_ibo);
		}

		m_indices = vector<int>(indices, indices + size);

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndices().size() * sizeof(int), getIndices().data(), GL_STATIC_DRAW);
	}

}