#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "ray.h"
#include "color.h"

class hit_record;

class material {
public :
    virtual ~material() = default;

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertian : public material {
private:
    color albedo;

public :
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

};

class metal : public material {
private:
    color albedo;
    double fuzziness;

public:
    metal(const color& albedo, double fuzziness) : albedo(albedo), fuzziness(fuzziness < 0 ? 0 : fuzziness){}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        
        vec3 reflected_direction = reflect(r_in.direction(), rec.normal);
        reflected_direction = unit_vector(reflected_direction) + (fuzziness * random_unit_vector());
        scattered = ray(rec.p, reflected_direction);
        attenuation = albedo;
        return true;
    }

};


class dielectric : public material {
private:
    double refraction_indice;

public:
    dielectric(double refraction_indice) : refraction_indice(refraction_indice) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {

        double etai_over_eta = rec.front_face ? (1.0 / refraction_indice) : refraction_indice;
        vec3 unit_incident_direction = unit_vector(r_in.direction());

        double cos_theta = std::fmin(dot(-unit_incident_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = etai_over_eta * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance_Schlick(cos_theta, etai_over_eta) > random_double()) { // reflection totale !!
            direction = reflect(unit_incident_direction, rec.normal);
        }
        else {
            direction = refract(unit_incident_direction, rec.normal, etai_over_eta);
            
        }
        scattered = ray(rec.p, direction);
        attenuation = color(1, 1, 1);
        return true;
    }
private:
    static double reflectance_Schlick(double cosine, double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

};

#endif 