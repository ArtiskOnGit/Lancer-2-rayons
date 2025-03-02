#include "vec3.h"


vec3 vec3::random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq) {
            return (p / std::sqrt(lensq));
        }
    }
}

vec3 vec3::random_on_hemisphere(const vec3& normal) {
    vec3 ruv = random_unit_vector();
    if (dot(ruv, normal) > 0.0) {
        return ruv;
    }
    return -ruv;
}