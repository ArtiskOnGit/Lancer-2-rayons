#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <iostream>



int main() {

    


    hittable_list world = hittable_list();
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
    auto material_up = make_shared<metal>(color(0.3, 0.3, 0.5), 0.0);
    auto material_dielec = make_shared<dielectric>(1.00 / 1.33);

    world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground)); // ground
    world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center)); // ball center
    world.add(make_shared<Sphere>(point3(0.0, 1.0, -1.2), 0.4, material_up)); // ball above
    world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left)); // left ball
    world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble)); // left ball
    world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right)); // right ball

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;


    cam.render(world);

}