#include "Includes/color.h"
#include "Includes/vec3.h"
#include "Includes/ray.h"

#include <iostream>



double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}



color ray_colour(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }


    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0; // = 1.77778
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio); // = 225
    image_height = (image_height < 1) ? 1 : image_height; 

    // Camera

    auto focal_length = 1; // = 1
    auto viewport_height = 2.0; // = 2
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height); // = 3.55556
    auto camera_center = point3(0, 0, 0); // = (0, 0, 0)

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0); // = (3.55556, 0, 0)
    auto viewport_v = vec3(0, -viewport_height, 0); // = (0, -2, 0)

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width; // = (0.00888889, 0, 0)
    auto pixel_delta_v = viewport_v / image_height; // = (0, 0.00888889, 0)

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2; // = (-1.77778, 1, -1)
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // = (-1.76889, 1.00889, -1)

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_colour(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";



}