#include "ray.h"

Ray::Ray(){}

Ray::Ray(const glm::vec3& a, const glm::vec3& b)
	:mOrigin(a), mDirection(b)
{
}