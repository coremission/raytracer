#pragma once
#include "hitable.h"

class HitableList: public Hitable {
	Hitable** list;
	int listSize;
public:
	virtual ~HitableList() override {};
	HitableList(): list(nullptr), listSize(0) {};
	HitableList(Hitable** l, int n) : list(l), listSize(n) {};
	virtual bool Hit(const Ray& r, float tmin, float tmax, HitRecord& rec) const override;
};