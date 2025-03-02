#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include "hittable.h"
#include <vector>



class hittable_list : public hittable {
public : 
	std::vector<shared_ptr<hittable>> objects;

	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	void clear() { objects.clear(); }


	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		hit_record temp_hit;
		bool hit_anything = false;
		interval checked_interval = ray_t;

		for (const auto& object : objects) {
			if (object->hit(r, checked_interval, temp_hit)) {
				hit_anything = true;
				checked_interval.max = temp_hit.t;
				rec = temp_hit;
			}
		}
		return hit_anything;
	}
};


#endif HITTABLE_LIST_H