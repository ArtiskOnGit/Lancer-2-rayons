#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>



color ray_color(const ray& r, const hittable_list& world) {

    hit_record hit;
    bool res = world.hit(r, interval(0, infinity), hit);
    if (res) {
        return 0.5*(hit.normal+color(1, 1, 1));
    }
    
    vec3 dir = unit_vector(r.direction());
    auto a = 0.5 * (dir.y() + 1.0);
    return (1.0 - a) * color(0, 0, 9.0) + a * color(0.8, 0.9, 1.0);
}

int main() {

    

    hittable_list world = hittable_list();
    world.add(make_shared<Sphere>(point3(0, 0, -1.0), 0.2));
    world.add(make_shared<Sphere>(point3(0.6, 0.6, -1.0), 0.5));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;

    cam.render(world);
}