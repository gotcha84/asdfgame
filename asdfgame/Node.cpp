#include "Node.h"

namespace sg {

	Node::Node(string name) {
		setName(name);
	}

	Node::~Node() {

	}

	ostream& Node::print(ostream &stream) {
		return stream << "Node(" << getName() << ")";
	}

	// name
	string Node::getName() {
		return m_name;
	}

	void Node::setName(string name) {
		m_name = name;
	}

	// parent
	Node* Node::getParent() {
		return m_parent;
	}

	void Node::setParent(Node *parent) {
		m_parent = parent;
	}

	bool Node::hasParent() {
		return (getParent() != nullptr);
	}

	void Node::removeParent() {
		setParent(nullptr);
	}

}


ostream& operator<<(ostream &stream, sg::Node &node) {
	return node.print(stream);
}

glm::mat4 getProjMatrix() {
	// Projection matrix : 45 deg FoV, 4:3 ratio, display range : 0.1 unit to 100 units
	return glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}