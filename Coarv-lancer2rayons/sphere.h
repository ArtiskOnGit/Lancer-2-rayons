#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h";
class Sphere : hittable {

private :
	point3 center;
	double radius;
public :
	Sphere(const point3 &c,const double &r) :center(c), radius(std::fmax(0, r)) {}

	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override{
        point3 c_q = center - r.origin();
        double a = r.direction().length_squared();
        double h = dot(r.direction(), c_q);
        double c = c_q.length_squared() - radius * radius;
        // double b = dot(-2.0 * r.direction(), c_q);

        double discrim = h * h - a * c;
        
        if (discrim < 0) { return false; }
        
        double root = (h - std::sqrt(discrim)) / a;

        if (ray_tmin <= root && root <= ray_tmax) {
            rec.t = root;
            rec.p = r.at(rec.t);
           // rec.normal = unit_vector(rec.p - center);
            rec.set_face_normal(r, unit_vector(rec.p - center));
            return true;
        }
        else {
            root = (h + std::sqrt(discrim)) / a;
            if (ray_tmin <= root && root <= ray_tmax) {
                rec.t = root;
                rec.p = r.at(rec.t);
                //rec.normal = unit_vector(rec.p - center);
                rec.set_face_normal(r, unit_vector(rec.p - center));
                
                return true;
            }
        }
        return false;
	}
};

#endif