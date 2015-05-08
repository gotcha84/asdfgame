#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <string>
#include <iostream>

using namespace std;

namespace sg {

	class Node {
		private:
			string m_name;
			Node *m_parent;

		public:
			Node(string name);
			~Node();

			virtual void draw(glm::mat4 parent, glm::mat4 viewMatrix) = 0;

			virtual ostream& print(ostream &stream);

			// name
			string getName();
			void setName(string name);

			// parent
			Node* getParent();
			void setParent(Node *parent);
			bool hasParent();
			void removeParent();
			
	};

}


ostream& operator<<(ostream &stream, sg::Node &node);
glm::mat4 getProjMatrix();

#endif