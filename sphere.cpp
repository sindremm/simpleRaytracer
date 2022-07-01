#include "sphere.h"

Sphere::Sphere(point sphere_center, double sphere_radius) : HittableObject{sphere_center}, radius{sphere_radius} {
    radius_squared = powf(radius, 2);
}