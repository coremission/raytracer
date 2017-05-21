#pragma once

#include <glm/glm.hpp>
#include "ray.h"
#include "hitable.h"

class Material {
public:
	virtual ~Material() {}
	virtual bool scatter(const Ray& rayIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scatteredRay) const = 0;
};

class Lambertian: public Material {
	glm::vec3 albedo;
public:
	Lambertian(const glm::vec3 _albedo): albedo(_albedo) {}
	virtual bool scatter(const Ray& rayIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scatteredRay) const override;
};

class Metal: public Material {
	glm::vec3 albedo;
public:
	Metal(const glm::vec3 _albedo): albedo(_albedo) {}
	virtual bool scatter(const Ray& rayIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scatteredRay) const override;
};