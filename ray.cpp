#include "ray.h"
#include <cmath>
#include <vector>
#include <numeric>

Ray::Ray(vec3 pos, vec3 dir, Object* src) : Object{pos}, direction{dir}, source{src} {}

void Ray::normalize() {
    std::cout << "lenght squared: " << direction.lenght_squared() << '\n';
    direction /= sqrtf(direction.lenght_squared());
}


vec3 Ray::get_ray_sphere_vector(Sphere target_sphere) {
    vec3 sphere_center = target_sphere.position;
    vec3 rs_vector;

    // create vector from origin to sphere center
    rs_vector = sphere_center - position;
    return rs_vector;
}

bool Ray::is_outside(double rs_squared, Sphere target_sphere) const {
    if (rs_squared < target_sphere.radius_squared) {
        return false;
    }
    return true;
};

double Ray::calculate_tca(vec3 rs_vector) {
    /*
    Take scalarproduct of ray-to-sphere vector and the normailzed ray vector. This gives the time t until the ray reaches
    the point closest to the sphere center. If this is positive, the ray points towards the sphere
    */
   //std::vector<double> rs {{rs_vector.x, rs_vector.y, rs_vector.z}};
   std::vector<double> a{};
   //std::vector<double> dir {direction.x, direction.y, direction.z};
   //return std::inner_product(dir.begin(), dir.end(), rs.begin(), 0.0);
};

double Ray::calculate_hc_square(double rs_squared, double tca, Sphere& target_sphere) const {};

double Ray::isect_dist(double hc_square, double tca) const {};

Ray Ray::intersection_normal(double intersection_distance, Sphere& target_sphere) const {};