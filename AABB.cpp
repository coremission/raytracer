#include "AABB.h"
#include "ray.h"
#include "functions.hpp"

AABB::AABB()
{
}

bool AABB::hit(const Ray& r, float tmin, float tmax) const {
	for(int a = 0; a < 3; a++) {
		float t0 = ffmin((min[a] - r.origin()[a]) / r.direction()[a],
			(max[a] - r.origin()[a]) / r.direction()[a]);
		float t1 = ffmax((min[a] - r.origin()[a]) / r.direction()[a],
			(max[a] - r.origin()[a]) / r.direction()[a]);

		tmin = ffmax(t0, tmin);
		tmax = ffmin(t1, tmax);
		if (tmax <= tmin)
			return false;
	}
	return true;
}

AABB::~AABB()
{
}
