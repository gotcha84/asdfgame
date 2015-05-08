#include "Geode.h"

namespace sg {

	Geode::Geode(string name) : Node(name) {

	}

	Geode::~Geode() {

	}

	ostream& Geode::print(ostream &stream) {
		return stream << "Geode(" + getName() + ")";
	}

	// getters
	glm::mat4 Geode::getModelMatrix() {
		return m_modelMatrix;
	}

	// setters
	void Geode::setModelMatrix(glm::mat4 modelMatrix) {
		m_modelMatrix = modelMatrix;
	}

}