#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
public:
    /* Public Camera Parameters Here */
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    void render(const hittable& world) {
        // Render
        initialize();
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);

                color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";

    }

private:
    /* Private Camera Variables Here */

    int image_height;
    double focal_length;
    double viewport_height, viewport_width;
    vec3 camera_center;
    vec3 viewport_u, viewport_v, pixel_delta_u, pixel_delta_v;
    vec3 viewport_upper_left, pixel00_loc;

    void initialize() {

        // Calculate the image height, and ensure that it's at least 1.
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        // Camera

        focal_length = 1.0;
        viewport_height = 2.0;
        viewport_width = viewport_height * (double(image_width) / image_height);
        camera_center = point3 (0, 0, 0);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        viewport_u = vec3(viewport_width, 0, 0);
        viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        viewport_upper_left = camera_center
            - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        
    }

    color ray_color(const ray& r, const hittable& world) const {
        hit_record hit;
        if (world.hit(r, interval(0, infinity), hit)) {
            return 0.5 * (hit.normal + color(1, 1, 1));
        }

        vec3 dir = unit_vector(r.direction());
        auto a = 0.5 * (dir.y() + 1.0);
        return (1.0 - a) * color(0, 0, 9.0) + a * color(0.8, 0.9, 1.0);
    }
};

#endif