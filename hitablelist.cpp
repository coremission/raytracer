#include "hitablelist.h"

bool HitableList::Hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const {
	HitRecord temp;
	bool hitAnything = false;

	float closestSoFar = tmax;
	for(int i = 0; i < listSize; ++i) {
		if(list[i]->Hit(r, tmin, tmax, temp)) {
			hitAnything = true;
			closestSoFar = temp.t;
			rec = temp;
		}
	}
	return hitAnything;
}