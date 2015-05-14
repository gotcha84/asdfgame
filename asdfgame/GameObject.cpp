#include "GameObject.h"

GameObject::GameObject(string name) {
	setName(name);
}

GameObject::~GameObject() {

}

ostream& GameObject::print(ostream &stream) {
	return stream << "GameObject(" << getName() << ")";
}

// getters
string GameObject::getName() {
	return m_name;
}

// setters
void GameObject::setName(string name) {
	m_name = name;
}


ostream& operator<<(ostream &stream, GameObject &gameObject) {
	return gameObject.print(stream);
}

glm::mat4 getProjMatrix() {
	// Projection matrix : 45 deg FoV, 4:3 ratio, display range : 0.1 unit to 100 units
	return glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}