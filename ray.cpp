#include "ray.h"
#include <cmath>
#include <vector>
#include <numeric>

Ray::Ray(point pos, vector dir, Object* src) : Object{pos}, direction{dir}, source{src} {}

void Ray::print() const {
    std::cout << "\tposition: \n";
    position.print();
    std::cout << "\tdirection: \n";
    direction.print();
}

vector Ray::get_ray_sphere_vector(Sphere target_sphere) {
    // find vector from the origin of the ray to the sphere center
    vector rs_vector = target_sphere.position - position;
    return rs_vector;
}

bool Ray::is_outside(double rs_squared, Sphere target_sphere) const {
    // Compares the squared length of the spheres radius and rays distance from sphere
    if (rs_squared < target_sphere.radius_squared) {
        return false;
    }
    return true;
};

double Ray::find_dot(vector rs_vector) {
    
    //If the dot product between the rays direction and the vector between the rays and
    //the spheres orogins is negative, the ray points away from the sphere.
    
   return dot(direction, rs_vector);
};

double Ray::find_half_chord_distance(double rs_squared, double tca, Sphere& target_sphere) const {
    //We find the closest approach between the ray and the sphere center 
    double closest_approach_squared =  rs_squared - tca*tca;
    // We can then find the half chord distance by again using the pythagorean theorem
    return target_sphere.radius_squared - closest_approach_squared;
    // If the half chord distance is negative, then the closest approach is larger than the spheres radius
    // and thus the ray misses the sphere
};

double Ray::find_intersection_distance(double hc_square, double tca) const {
    // The distance from the ray origin to the surface of the sphere can be found by subtracting
    // the half chord distance from the lenght at closest approach
    return tca - sqrt(hc_square);
};

Ray Ray::find_intersection_normal(double intersection_distance, Sphere& target_sphere) const {
    point normal_position;
    vector normal_direction;

    for (int i = 0; i < 3; i++) {
        double n_coordinate = position.at(i) + direction.at(i) * intersection_distance;
        normal_position.at(i) = n_coordinate;
        normal_direction.at(i) = n_coordinate - target_sphere.position.at(i);
    }
    normal_direction = unit_vector(normal_direction);

    Object* ts = &target_sphere;
    return Ray{normal_position, normal_direction, ts};

    
};


color Ray::shoot(Sphere& target_sphere) {
    //testing
    //if (this->direction.x() )
    // Miss color
    color miss{100, 100, 100};
   

    // Fin the ray to sphere vector and calculate the squared distance
    vector rs_vector = get_ray_sphere_vector(target_sphere);
    double rs_squared = dot(rs_vector, rs_vector);

    // Stop if ray is inside sphere
    if (!is_outside(rs_squared, target_sphere)) {
        return miss;
    }

    // Stop if ray points away from sphere
    //double tca = find_dot(rs_vector);
    vector tca_vec = direction * dot(rs_vector, direction) ;
    double tca = tca_vec.length();
    if (tca  <= 0) {
        return miss;
    }

    // Stop if ray misses sphere
    double hc_square = find_half_chord_distance(rs_squared, tca, target_sphere);
    if (hc_square < 0) {
        return miss;
    }

    // Get intersection distance and calculate normal
    double inter_dist = find_intersection_distance(hc_square, tca);
    // std::cout << "intersection distance: " << inter_dist << '\n';
    Ray normal = find_intersection_normal(inter_dist, target_sphere);
    // std::cout << "normal: \n";
    return target_sphere.color_value;

}
