#pragma once
#include <glm/glm.hpp>

#include "hitable.h"

class Sphere: public Hitable {
	glm::vec3 center;
	float radius;

public:
	Sphere() {};
	virtual ~Sphere() override {};
	Sphere(glm::vec3 _center, float _radius) : center(_center), radius(_radius) {};
	virtual bool Hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const override;
};