#pragma once
#include <glm/glm.hpp>
#include "ray.h"
#include "AABB.h"

class Material;
struct HitRecord {
	float t;
	glm::vec3 p;
	glm::vec3 normal;
	Material* material;
};

class Hitable {
public:
	virtual ~Hitable() {}
	virtual bool Hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
	virtual bool BoundingBox(float t0, float t1, AABB& box) const = 0;
};