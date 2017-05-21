#include <iostream>
#include <glm/glm.hpp>
#include <random>

#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"

using namespace glm;

float random() {
	return float(rand()) / float(RAND_MAX);
}

vec3 randomInUnitSphere() {
	vec3 p = normalize(vec3(random(), random(), random()));
	/*do {
		p = 2.0f * vec3(random(), random(), random()) - vec3(1.f, 1.f, 1.f);
	} while (p.length() * p.length() >= 1.0f);
	*/
	return p;
}

vec3 color(const Ray& r, Hitable* world) {
	HitRecord rec;

	if(world->Hit(r, 0.0, 9999999.f, rec)) {
		vec3 target = rec.p + rec.normal + randomInUnitSphere();
		return 0.5f * color(Ray(rec.p, target), world);
	}
	// gradient for background
	vec3 unit_direction = normalize(r.direction());
	float t = 0.5f * (unit_direction.y + 1.f);

	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}
void debug(){}

int main(int argc, char** argv) {
	int nx = 200;
	int ny = 200;
	int ns = 16;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	Hitable* list[2];
	list[0] = new Sphere(vec3(0.f, 0.f, -1.f), 0.5f);
	list[1] = new Sphere(vec3(0.f, -100.5f, -1.f), 100);
	Hitable* world = new HitableList(list, 2);
	Camera cam;
	for(int y = ny - 1; y > 0; --y) {
		for(int x = 0; x < nx; ++x) {
			vec3 c(0.f, 0.f, 0.f);
			for(int s = 0; s < ns; ++s) {
				if (y == 50 && x == 100) {
					debug();
				}

				float u = float(y + random()) / float(ny);
				float v = float(x + random()) / float(nx);

				Ray r = cam.getRay(u, v);
				c += color(r, world);
			}
			
			c /= float(ns);
			// gamma correction
			c = vec3(sqrt(c.x), sqrt(c.y), sqrt(c.z));

			int ir = int(255.99 * c.r);
			int ig = int(255.99 * c.g);
			int ib = int(255.99 * c.b);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}