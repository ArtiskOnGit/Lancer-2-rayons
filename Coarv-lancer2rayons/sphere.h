#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public hittable {

private :
	point3 center;
	double radius;
    shared_ptr<material> mat;
public :
	Sphere(const point3 &c,const double &r, shared_ptr<material> mat) :center(c), radius(std::fmax(0, r)), mat(mat) {}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override{
        point3 c_q = center - r.origin();
        double a = r.direction().length_squared();
        double h = dot(r.direction(), c_q);
        double c = c_q.length_squared() - radius * radius;
        // double b = dot(-2.0 * r.direction(), c_q);

        double discrim = h * h - a * c;
        
        if (discrim < 0) { return false; }
        
        double root = (h - std::sqrt(discrim)) / a;

        if (ray_t.surrounds(root)) {
            rec.t = root;
            rec.p = r.at(rec.t);
            rec.set_face_normal(r, unit_vector(rec.p - center));
            rec.mat = mat;

            return true;
        }
        else {
            root = (h + std::sqrt(discrim)) / a;
            if (ray_t.surrounds(root)) {
                rec.t = root;
                rec.p = r.at(rec.t);
                rec.set_face_normal(r, unit_vector(rec.p - center));
                rec.mat = mat;
                
                return true;
            }
        }
        return false;
	}
};

#endif