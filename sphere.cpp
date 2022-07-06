#include "sphere.h"

Sphere::Sphere(point sphere_center, color sphere_color, double sphere_radius) : HittableObject{sphere_center, sphere_color}, radius{sphere_radius} {
    radius_squared = powf(radius, 2);
}