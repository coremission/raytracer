#pragma once

#include <glm/glm.hpp>
#include "ray.h"

class Camera {
	glm::vec3 origin; // camera position
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
public:
	Camera() :
		origin(glm::vec3(0.f, 0.f, 0.f)),
		lowerLeftCorner(glm::vec3(-2.f, -1.f, -1.f)),
		horizontal(glm::vec3(4.f, 0.f, 0.f)),
		vertical(glm::vec3(0.f, 2.f, 0.f))
	{};
	Ray getRay(float u, float v) {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}
};