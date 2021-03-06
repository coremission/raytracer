#pragma once
#include <glm/glm.hpp>

#include "hitable.h"

class Sphere: public Hitable {
	glm::vec3 center;
	float radius;
	Material* material;
public:
	inline Material* getMaterial() const { return material; }
	virtual ~Sphere() override {};
	Sphere(Material* mat, glm::vec3 _center, float _radius): material(mat), center(_center), radius(_radius) {};
	virtual bool Hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const override;
	virtual bool BoundingBox(float t0, float t1, AABB& box) const override {
		box = AABB(center - glm::vec3(radius, radius, radius), center + glm::vec3(radius, radius, radius));
		return true;
	}
};