#include "AABB.h"

AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	m_minX = minX;
	m_minY = minY;
	m_minZ = minZ;
	
	m_maxX = maxX;
	m_maxY = maxY;
	m_maxZ = maxZ;
}

AABB::AABB(glm::vec3 min, glm::vec3 max) {
	AABB(min.x, min.y, min.z, max.x, max.y, max.z);
}

AABB::~AABB() {

}

bool AABB::collidesWith(AABB *other) {
	return other->m_maxX > m_minX && other->m_minX < m_maxX
		&& other->m_maxY > m_minY && other->m_minY < m_maxY
		&& other->m_maxZ > m_minZ && other->m_minZ < m_maxZ;
}
