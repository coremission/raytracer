#pragma once
#include <glm/glm.hpp>
#include "ray.h"

class AABB {
private:
	glm::vec3 min;
	glm::vec3 max;

public:
	glm::vec3 getMin() const { return min; }
	glm::vec3 getMax() const { return max; }

	AABB();
	AABB(const glm::vec3& a, const glm::vec3& b)
	:min(a),max(b){}

	bool hit(const Ray& r, float tmin, float tmax) const;
	~AABB();
};

