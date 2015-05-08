#ifndef BASICGEODE_H
#define BASICGEODE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Geode.h"

namespace sg {
	class BasicGeode : public Geode {
		private:
			GLuint m_shaderProgramId;

			vector<float> m_vertices;
			vector<int> m_indices;
			
			GLuint m_vbo;
			bool m_vboExists;

			GLuint m_ibo;
			bool m_iboExists;

		public:
			BasicGeode(string name);
			~BasicGeode();

			virtual void draw(glm::mat4 parent, glm::mat4 viewMatrix);

			// getters
			vector<float> getVertices();
			vector<int> getIndices();

			// setters
			void setVertices(vector<float> vertices);
			void setVertices(float *vertices, int size);

			void setIndices(vector<int> indices);
			void setIndices(int *indices, int size);
	};
}

#endif