#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include <iostream>




int main() {

    

    hittable_list world = hittable_list();
    world.add(make_shared<Sphere>(point3(0, 0, -1.0), 0.2));
    world.add(make_shared<Sphere>(point3(0.6, 0.6, -1.0), 0.5));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;

    cam.render(world);
}