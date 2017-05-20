#include <iostream>
#include <glm/glm.hpp>

#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"

using namespace glm;

vec3 color(const Ray& r, Hitable* world) {
	HitRecord rec;

	if(world->Hit(r, 0.0, 9999999.f, rec)) {
		return 0.5f * rec.normal + vec3(1.f, 1.f, 1.f);
	}
	else {
		vec3 unit_direction = normalize(r.direction());
		float t = 0.5f * (unit_direction.y + 1.f);

		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main(int argc, char** argv) {
	int width = 400;
	int height = 200;

	std::cout << "P3\n" << width << " " << height << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0, 0.0);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	Hitable* list[2];
	list[0] = new Sphere(vec3(0.f, 0.f, -1.f), 0.5f);
	list[1] = new Sphere(vec3(0.f, -100.5f, -1.f), 100);
	Hitable* world = new HitableList(list, 2);

	for(int i = height - 1; i > 0; --i) {
		for(int j = 0; j < width; ++j) {

			float u = float(i) / float(height);
			float v = float(j) / float(width);

			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 c = color(r, world);

			int ir = int(255.99 * c.r);
			int ig = int(255.99 * c.g);
			int ib = int(255.99 * c.b);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}