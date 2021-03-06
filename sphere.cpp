#include <glm/glm.hpp>
#include "sphere.h"

using namespace glm;

bool Sphere::Hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const {
	vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float D = b * b - a * c;
	if(D > 0) {
		float temp = (-b - sqrt(D)) / a;
		if(temp < tmax && temp > tmin) {
			rec.t = temp;
			rec.material = getMaterial();
			rec.p = r.pointAtParameter(temp);
			rec.normal = normalize((rec.p - center) / radius);
			return true;
		}

		temp = (-b + sqrt(D)) / a;
		if (temp < tmax && temp > tmin) {
			rec.t = temp;
			rec.material = getMaterial();
			rec.p = r.pointAtParameter(temp);
			rec.normal = normalize((rec.p - center) / radius);
			return true;
		}
	}

	return false;
}