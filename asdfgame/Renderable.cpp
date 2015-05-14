#include "Renderable.h"

#include "Shader.h"

namespace game {

	Renderable::Renderable(string name, Model *model, string vertex) : Object(name) {
		setModel(model);

		setModelMatrix(glm::mat4(1.0f));

		m_shaderProgramId = Shader::loadShaders(vertex.c_str(), "simple.frag");
	}

	Renderable::~Renderable() {
		setModel(nullptr);

		glDeleteProgram(m_shaderProgramId);
	}

	void Renderable::draw(glm::mat4 viewMatrix) {
		// calculate MVP matrix
		glm::mat4 mvpMatrix = getProjMatrix() * viewMatrix * getModelMatrix();

		// shader
		glUseProgram(m_shaderProgramId);
		GLuint mvpMatrixId = glGetUniformLocation(m_shaderProgramId, "mvpMatrix");
		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);

		getModel()->draw();
	}

	ostream& Renderable::print(ostream &stream) {
		return stream << "Renderable(" + getName() + ")";
	}

	// getters
	glm::mat4 Renderable::getModelMatrix() {
		return m_modelMatrix;
	}

	Model* Renderable::getModel() {
		return m_model;
	}

	// setters
	void Renderable::setModelMatrix(glm::mat4 modelMatrix) {
		m_modelMatrix = modelMatrix;
	}

	void Renderable::setModel(Model *model) {
		m_model = model;
	}

}
