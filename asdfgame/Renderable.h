#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Object.h"
#include "Model.h"

namespace game {

	class Renderable : public game::Object {
		private:
			GLuint m_shaderProgramId;
			glm::mat4 m_modelMatrix;
			Model *m_model;

		public:
			Renderable(string name, Model *model, string vertex);
			~Renderable();

			virtual void draw(glm::mat4 viewMatrix);

			virtual ostream& print(ostream &stream);

			// getters
			glm::mat4 getModelMatrix();
			Model* getModel();

			// setters
			void setModelMatrix(glm::mat4 modelMatrix);
			void setModel(Model *model);
	};

}

#endif