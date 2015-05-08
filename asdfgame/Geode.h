#ifndef GEODE_H
#define GEODE_H

#include "Node.h"
#include "AABB.h"

namespace sg {

	class Geode : public Node {
		private:
			glm::mat4 m_modelMatrix;
			AABB *m_bbox;

			//virtual void calculateBoundingBox() = 0;

		public:
			Geode(string name);
			~Geode();

			virtual void draw(glm::mat4 parent, glm::mat4 viewMatrix) = 0;
			
			virtual ostream& print(ostream &stream);

			// getters
			glm::mat4 getModelMatrix();

			// setters
			void setModelMatrix(glm::mat4 modelMatrix);
	};

}

#endif