#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "hittable.h"

class camera {
public:
    /* Public Camera Parameters Here */
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int    samples_per_pixel = 10;   // Count of random samples for each pixel

    void render(const hittable& world) {
        // Render
        initialize();
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";

    }

private:
    /* Private Camera Variables Here */

    int image_height;
    double pixel_samples_scale;
    double focal_length;
    double viewport_height, viewport_width;
    vec3 camera_center;
    vec3 viewport_u, viewport_v, pixel_delta_u, pixel_delta_v;
    vec3 viewport_upper_left, pixel00_loc;

    void initialize() {

        // Calculate the image height, and ensure that it's at least 1.
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        pixel_samples_scale = 1.0 / samples_per_pixel;

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
            vec3 random_direction = vec3::random_on_hemisphere(hit.normal);
            return 0.5 * (hit.normal + color(1, 1, 1));
        }

        vec3 dir = unit_vector(r.direction());
        auto a = 0.5 * (dir.y() + 1.0);
        return (1.0 - a) * color(0, 0, 9.0) + a * color(0.8, 0.9, 1.0);
    }


    ray get_ray(int i, int j) {
        // Construct a camera ray originating from the origin and directed at randomly sampled
       // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
            + ((i + offset.x()) * pixel_delta_u)
            + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);

    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
};

#endif