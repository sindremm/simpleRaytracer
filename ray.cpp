#include "ray.h"

Ray::Ray(vec3 pos, vec3 dir) : Object{pos}, direction{dir} {}

void Ray::normalize() {
    std::cout << "lenght squared: " << direction.lenght_squared() << '\n';
    direction /= sqrtf(direction.lenght_squared());
}