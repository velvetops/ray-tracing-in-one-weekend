#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ray.hpp"

vec3 random_in_unit_disk() {
    vec3 p;
    while (dot(p, p) >= 1.0) {
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    }
    return p;
}

class camera {
   public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;

    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
           float aperture, float focus_dist) {
        lens_radius = aperture / 2;
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        // lower_left_corner = vec3(-half_width, -half_height, -1.0);
        lower_left_corner = origin - focus_dist * half_width * u -
                            focus_dist * half_height * v - focus_dist * w;
        horizontal = 2 * focus_dist * half_width * u;
        vertical = 2 * focus_dist * half_height * v;
    }

    ray get_ray(float s, float t) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lower_left_corner + s * horizontal +
                                        t * vertical - origin - offset);
    }
};

#endif