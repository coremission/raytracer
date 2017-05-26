#pragma once

#include <glm/glm.hpp>
#include "ray.h"

class Camera {
	glm::vec3 origin; // camera position
	glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	float aperture;
	float focusDistance;
	glm::vec3 u;
	glm::vec3 v;
	glm::vec3 w;
public:
	Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 upVector, float verticalFov,
		float aspect, float aperture, float focusDistance);
	Ray getRay(float u, float v);
};