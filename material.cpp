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
	scatteredRay = Ray(rec.p, reflected);
	attenuation = albedo;
	return dot(scatteredRay.direction(), rec.normal) > 0;
}