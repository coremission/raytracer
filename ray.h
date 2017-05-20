#pragma once
#include <glm/glm.hpp>

class ray {
	glm::vec3 mOrigin;
	glm::vec3 mDirection;
public:
	ray();
	ray(const glm::vec3& a, const glm::vec3& b);
	
	glm::vec3 origin() const { return mOrigin; }
	glm::vec3 direction() const { return mDirection; }

	glm::vec3 pointAtParameter(float t) const { return mOrigin + t * mDirection; };
};