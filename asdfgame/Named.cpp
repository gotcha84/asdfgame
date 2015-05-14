#include "Named.h"

Named::Named(string name) {
	m_name = name;
}

// getters
string Named::getName() {
	return m_name;
}

// setters
void Named::setName(string name) {
	m_name = name;
}
