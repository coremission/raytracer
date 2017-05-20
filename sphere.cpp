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
		float temp = (-b - sqrt(b*b - a*c)) / a;
		if(temp < tmax, temp > tmin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}

		temp = (-b + sqrt(b*b - a*c)) / a;
		if (temp < tmax && temp > tmin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}