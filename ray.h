#pragma once
#include <glm/glm.hpp>

class Ray {
	glm::vec3 mOrigin;
	glm::vec3 mDirection;
public:
	Ray::Ray() {};
	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
		:mOrigin(origin), mDirection(glm::normalize(direction))
	{};
	
	glm::vec3 origin() const { return mOrigin; }
	glm::vec3 direction() const { return mDirection; }
	glm::vec3 pointAtParameter(float t) const { return mOrigin + t * mDirection; };
};