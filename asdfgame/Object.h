#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <string>
#include <iostream>

#include "Named.h"

using namespace std;

namespace game {

	class Object : public Named {
		private:

		public:
			Object(string name);
			~Object();

			virtual ostream& print(ostream &stream);
	};

}

ostream& operator<<(ostream &stream, game::Object &object);
glm::mat4 getProjMatrix();

#endif