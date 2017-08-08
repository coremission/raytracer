#include "hitablelist.h"
#include "functions.hpp"

bool HitableList::Hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const {
	HitRecord temp;
	bool hitAnything = false;

	float closestSoFar = tmax;
	for(int i = 0; i < listSize; ++i) {
		if(list[i]->Hit(r, tmin, closestSoFar, temp)) {
			hitAnything = true;
			closestSoFar = temp.t;
			rec = temp;
		}
	}
	return hitAnything;
}

AABB HitableList::SurroundingBox(AABB& box0, AABB& box1) const {
	glm::vec3 small(ffmin(box0.getMin().x, box1.getMin().x),
		ffmin(box0.getMin().y, box1.getMin().y),
		ffmin(box0.getMin().z, box1.getMin().z));

	glm::vec3 big(ffmax(box0.getMax().x, box1.getMax().x),
					ffmax(box0.getMax().y, box1.getMax().y),
					ffmax(box0.getMax().z, box1.getMax().z));
	
	return AABB(small, big);
}

bool HitableList::BoundingBox(float t0, float t1, AABB& box) const {
	if (listSize < 1)
		return false;

	AABB tempBox;
	bool firstTrue = list[0]->BoundingBox(t0, t1, tempBox);
	if (!firstTrue)
		return false;
	else
		box = tempBox;
	for(int i = 1; i < listSize; i++) {
		if (list[0]->BoundingBox(t0, t1, tempBox)) {
			box = SurroundingBox(box, tempBox);
		}
		else
			return false;
	}
	return true;
}