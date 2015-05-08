#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class AABB {
	private:
		float m_minX;
		float m_minY;
		float m_minZ;

		float m_maxX;
		float m_maxY;
		float m_maxZ;

	public:
		AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		AABB(glm::vec3 min, glm::vec3 max);
		~AABB();

		virtual bool collidesWith(AABB *other);
};

#endif