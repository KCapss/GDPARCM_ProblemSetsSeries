#pragma once
#include "hitable.h"
#include "material.h"

#ifndef SPHEREH
#define SPHEREH

class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material *mat) : center(cen), radius(r), matType(&*mat) {};

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

	vec3 center;
	float radius;
	
	//Temporary Solution: Remove when not needed
	material *matType;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b -  a * c;

	if (discriminant > 0) {
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_perimeter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = matType; //Place holder Solution for missing material
			return true;
		}

		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_perimeter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = matType; //Place holder Solution for missing material
			return true;
		}
	}
	return false;
}

inline vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0f);
	return p;
}

#endif // !SPHEREH

