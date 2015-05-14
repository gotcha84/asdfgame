#include "RenderableGO.h"

#include "Shader.h"


RenderableGO::RenderableGO(string name) : GameObject(name) {
	m_shaderProgramId = Shader::loadShaders("simple.vert", "simple.frag");
		
	glGenVertexArrays(1, &m_vao);
	m_dirty = true;

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_indexBuffer);
	glGenBuffers(1, &m_colorBuffer);
}

RenderableGO::~RenderableGO() {
	glDeleteProgram(m_shaderProgramId);

	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_colorBuffer);

	glDeleteVertexArrays(1, &m_vao);
}

void RenderableGO::fillBuffers() {
	glBindVertexArray(m_vao);

	// vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, getVertices().size() * sizeof(float), getVertices().data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, getColors().size() * sizeof(float), getColors().data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndices().size() * sizeof(int), getIndices().data(), GL_STATIC_DRAW);
}

void RenderableGO::draw(glm::mat4 parent, glm::mat4 viewMatrix) {
	// calculate MVP matrix
	glm::mat4 modelMatrix = parent * getModelMatrix();
	glm::mat4 mvpMatrix = getProjMatrix() * viewMatrix * modelMatrix;

	// shader
	glUseProgram(m_shaderProgramId);
	GLuint mvpMatrixId = glGetUniformLocation(m_shaderProgramId, "mvpMatrix");
	glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);

	// update buffers if new data
	if (m_dirty) {
		fillBuffers();
		m_dirty = false;
	}

	// draw
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, getIndices().size(), GL_UNSIGNED_INT, (void *)0);
}

ostream& RenderableGO::print(ostream &stream) {
	return stream << "RenderableGO(" + getName() + ")";
}

// getters
glm::mat4 RenderableGO::getModelMatrix() {
	return m_modelMatrix;
}

vector<float> RenderableGO::getVertices() {
	return m_vertices;
}

vector<int> RenderableGO::getIndices() {
	return m_indices;
}

vector<float> RenderableGO::getColors() {
	return m_colors;
}

// setters
void RenderableGO::setModelMatrix(glm::mat4 modelMatrix) {
	m_modelMatrix = modelMatrix;
}

void RenderableGO::setVertices(float *vertices, int size) {
	m_vertices = vector<float>(vertices, vertices + size);
	m_dirty = true;
}

void RenderableGO::setIndices(int *indices, int size) {
	m_indices = vector<int>(indices, indices + size);
	m_dirty = true;
}

void RenderableGO::setColors(float *colors, int size) {
	m_colors = vector<float>(colors, colors + size);
	m_dirty = true;
}
