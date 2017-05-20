#include <iostream>
#include <glm/glm.hpp>

#include "ray.h"

using namespace glm;

float hitSphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float D = b * b - 4 * a * c;

	if (D < 0)
		return -1.0f;
	return (-b - sqrt(D)) / 2.0f * a;
}

vec3 color(const ray& r) {
	vec3 sphereCenter = vec3(0.0f, 0.0f, -1.0f);

	float t = hitSphere(sphereCenter, 0.5f, r);
	
	if(t > 0.f) {
		vec3 N = normalize(r.pointAtParameter(t) - sphereCenter);
		return 0.5f * (N + vec3(1.f, 1.f, 1.f));
	}

	vec3 unit_direction = normalize(r.direction());
	t = 0.5f * (unit_direction.y + 1.0f);

	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main(int argc, char** argv) {
	int width = 200;
	int height = 100;

	std::cout << "P3\n" << width << " " << height << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0, 0.0);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	for(int i = height - 1; i > 0; --i) {
		for(int j = 0; j < width; ++j) {

			float u = float(i) / float(height);
			float v = float(j) / float(width);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 c = color(r);

			int ir = int(255.99 * c.r);
			int ig = int(255.99 * c.g);
			int ib = int(255.99 * c.b);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}