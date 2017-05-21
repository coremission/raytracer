#pragma once
#include <glm/glm.hpp>
#include "ray.h"

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
};