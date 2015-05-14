#include "Model.h"

#include "Shader.h"

/*
	private
*/

void Model::fillBuffers() {
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


/*
	public
*/

Model::Model(string name) : Named(name) {
	m_dirty = true;

	glGenVertexArrays(1, &m_vao);

	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_indexBuffer);
	glGenBuffers(1, &m_colorBuffer);
}

Model::~Model() {
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_colorBuffer);

	glDeleteVertexArrays(1, &m_vao);
}

void Model::draw() {
	// update buffers if new data
	if (m_dirty) {
		fillBuffers();
		m_dirty = false;
	}

	// draw
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, getIndices().size(), GL_UNSIGNED_INT, (void *)0);
}

// getters
vector<float> Model::getVertices() {
	return m_vertices;
}

vector<int> Model::getIndices() {
	return m_indices;
}

vector<float> Model::getColors() {
	return m_colors;
}

// setters
void Model::setVertices(float *vertices, int size) {
	m_vertices = vector<float>(vertices, vertices + size);
	m_dirty = true;
}

void Model::setIndices(int *indices, int size) {
	m_indices = vector<int>(indices, indices + size);
	m_dirty = true;
}

void Model::setColors(float *colors, int size) {
	m_colors = vector<float>(colors, colors + size);
	m_dirty = true;
}
