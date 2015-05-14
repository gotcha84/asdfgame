#include "Object.h"

namespace game {

	Object::Object(string name) : Named(name) {

	}

	Object::~Object() {

	}

	ostream& Object::print(ostream &stream) {
		return stream << "Object(" << getName() << ")";
	}

}

ostream& operator<<(ostream &stream, game::Object &object) {
	return object.print(stream);
}

glm::mat4 getProjMatrix() {
	// Projection matrix : 45 deg FoV, 4:3 ratio, display range : 0.1 unit to 100 units
	return glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}
