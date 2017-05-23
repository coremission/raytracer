#include "material.h"
#include <glm/glm.hpp>

using namespace glm;

static float random() {
	return float(rand()) / float(RAND_MAX);
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

vec3 randomInUnitSphere() {
	vec3 p = normalize(vec3(random(), random(), random()));
	/*do {
	p = 2.0f * vec3(random(), random(), random()) - vec3(1.f, 1.f, 1.f);
	} while (p.length() * p.length() >= 1.0f);
	*/
	return p;
}
bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scatteredRay) const {
	vec3 target = rec.p + rec.normal + randomInUnitSphere();
	scatteredRay = Ray(rec.p, target);
	attenuation = albedo;
	return true;
}

bool Metal::scatter(const Ray& rayIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scatteredRay) const {
	vec3 reflected = reflect(normalize(rayIn.direction()), rec.normal);
	scatteredRay = Ray(rec.p, reflected + fuzz * randomInUnitSphere());
	attenuation = albedo;
	return dot(scatteredRay.direction(), rec.normal) > 0;
}

bool refract(const vec3& v, const vec3& n, float coefficient, vec3& refracted) {
	vec3 unitV = normalize(v);
	float dt = dot(unitV, n);

	float discriminant = 1.f - coefficient * coefficient * (1 - dt * dt);
	if(discriminant > 0) {
		refracted = coefficient * (v - n * dt) - n * sqrt(discriminant);
		return true;
	}

	return false;
}

float schlick(float cosine, float refIdx) {
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 = r0*r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5.f);
}

bool Dielectric::scatter(const Ray & rayIn, const HitRecord & rec, glm::vec3 & attenuation, Ray & scatteredRay) const
{
	vec3 outwardNormal;
	vec3 reflected = reflect(rayIn.direction(), rec.normal);

	float coeff;
	attenuation = vec3(1.f, 1.f, 1.f);
	vec3 refracted;
	float reflectProb;
	float cosine;

	if(dot(rayIn.direction(), rec.normal) > 0) {
		outwardNormal = -rec.normal;
		coeff = refIdx;
		cosine = refIdx + dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
	}
	else {
		outwardNormal = rec.normal;
		coeff = 1.f / refIdx;
		cosine = -dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
	}

	if(refract(rayIn.direction(), outwardNormal, coeff, refracted)) {
		scatteredRay = Ray(rec.p, reflected);
		reflectProb = schlick(cosine, refIdx);
	}
	else {
		scatteredRay = Ray(rec.p, reflected);
		reflectProb = 1.f;
	}

	if(random() < reflectProb) {
		scatteredRay = Ray(rec.p, reflected);
	}
	else {
		scatteredRay = Ray(rec.p, refracted);
	}
	return true;
}
