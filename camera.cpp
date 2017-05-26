#include "camera.h"

using namespace glm;

float random();

Camera::Camera(glm::vec3 position, glm::vec3 lookAt,
	glm::vec3 upVector, float verticalFov, float aspect,
	float _aperture, float _focusDistance):
	origin(position),
	aperture(_aperture),
	focusDistance(_focusDistance)
{
	float theta = verticalFov;
	float halfHeight = tan(theta / 2.f);
	float halfWidth = aspect * halfHeight;

	w = normalize(position - lookAt);
	u = normalize(cross(upVector, w));
	v = cross(w, u);

	lowerLeftCorner = origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
	horizontal = 2 * halfWidth * focusDistance * u;
	vertical = 2 * halfHeight * focusDistance *v;
}

vec3 randomInUnitDisk() {
	vec3 p = normalize(vec3(random(), random(), random()));
	/*do {
	p = 2.0f * vec3(random(), random(), random()) - vec3(1.f, 1.f, 1.f);
	} while (p.length() * p.length() >= 1.0f);
	*/
	return p;
}

Ray Camera::getRay(float u, float v) {
	vec3 rd = aperture / 2.f * randomInUnitDisk();
	//vec3 offset = u * rd.x + v * rd.y;

	return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}