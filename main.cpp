#include <iostream>
#include <glm/glm.hpp>
#include <random>

#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

using namespace glm;

float random() {
	return float(rand()) / float(RAND_MAX);
}

vec3 color(const Ray& r, Hitable* world, int depth) {
	HitRecord rec;

	if(world->Hit(r, 0.0001f, 9999999.f, rec)) {
		Ray scatteredRay;
		vec3 attenuation;
		if(depth < 50 && rec.material->scatter(r, rec, attenuation, scatteredRay)) {
			return attenuation * color(scatteredRay, world, depth + 1);
		}
		return vec3(0.f, 0.f, 0.f);
	}
	// gradient for background
	vec3 unit_direction = normalize(r.direction());
	float t = 0.5f * (unit_direction.y + 1.f);

	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}
void debug(){}

int main(int argc, char** argv) {
	int nx = 400;
	int ny = 400;
	int ns = 80;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	constexpr int count = 4;
	Hitable* list[count];
	list[0] = new Sphere(new Lambertian(vec3(0.2f, 0.3f, 0.5f)), vec3(0.f, 0.f, -1.f), 0.5f);
	list[1] = new Sphere(new Lambertian(vec3(0.2f, 0.9f, 0.1f)), vec3(0.f, -100.5f, -1.f), 100);
	list[2] = new Sphere(new Metal(vec3(0.8f, 0.3f, 0.1f), 1.f), vec3(1.f, 0.f, -1.f), 0.5f);
	list[3] = new Sphere(new Dielectric(1.5f), vec3(-1.f, 0.f, -1.f), 0.5f);

	Hitable* world = new HitableList(list, count);

	const float aspect = float(nx) / float(ny);
	const float fov = 1.1f;
	const vec3 upDirection = vec3(0, 1, 0);
	const vec3 cameraPosition = vec3(-2, 2, 1);
	const vec3 lookAtPosition = vec3(0, 0, -1);
	const float focalDistance = glm::length(lookAtPosition - cameraPosition);
	const float apperture = 1.5f;
	Camera cam(cameraPosition, lookAtPosition, upDirection, fov, aspect, apperture, focalDistance);

	for(int y = ny - 1; y > 0; --y) {
		for(int x = 0; x < nx; ++x) {
			vec3 c(0.f, 0.f, 0.f);
			for(int s = 0; s < ns; ++s) {
				if (y == 50 && x == 100) {
					debug();
				}

				float u = float(x + random()) / float(nx);
				float v = float(y + random()) / float(ny);
				
				Ray r = cam.getRay(u, v);
				c += color(r, world, 0);
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