#include "sphere.h"

Sphere::Sphere(point sphere_center, color sphere_color, double sphere_radius) : HittableObject{sphere_center, sphere_color}, radius{sphere_radius} {
    radius_squared = powf(radius, 2);
}


vector Sphere::get_ray_sphere_vector(const BaseRay& incoming_ray) const {
    // find vector from the origin of the ray to the sphere center
    vector rs_vector = position - incoming_ray.position;
    return rs_vector;
}

bool Sphere::is_outside(double rs_squared, const BaseRay& incoming_ray) const {
    // Compares the squared length of the spheres radius and rays distance from sphere
    if (rs_squared < radius_squared) {
        return false;
    }
    return true;
};

double Sphere::find_dot(vector rs_vector, const BaseRay& incoming_ray) {
    
    //If the dot product between the rays direction and the vector between the rays and
    //the spheres orogins is negative, the ray points away from the sphere.
    
   return dot(incoming_ray.direction, rs_vector);
};

double Sphere::find_half_chord_distance(double rs_squared, double tca, const BaseRay& incoming_ray) const {
    //We find the closest approach between the ray and the sphere center 
    double closest_approach_squared =  rs_squared - tca*tca;
    // We can then find the half chord distance by again using the pythagorean theorem
    return radius_squared - closest_approach_squared;
    // If the half chord distance is negative, then the closest approach is larger than the spheres radius
    // and thus the ray misses the sphere
};

double Sphere::find_intersection_distance(double hc_square, double tca) const {
    // The distance from the ray origin to the surface of the sphere can be found by subtracting
    // the half chord distance from the lenght at closest approach
    return tca - sqrt(hc_square);
};

BounceRay Sphere::find_intersection_normal(double intersection_distance, const BaseRay& incoming_ray) const {
    point normal_position;
    vector normal_direction;

    for (int i = 0; i < 3; i++) {
        double n_coordinate = incoming_ray.position.at(i) + incoming_ray.direction.at(i) * intersection_distance;
        normal_position.at(i) = n_coordinate;
        normal_direction.at(i) = n_coordinate - position.at(i);
    }
    normal_direction = unit_vector(normal_direction);

    // Object* ts = &target_sphere;
    const VisibleObject* ts = this;
    return BounceRay{normal_position, normal_direction, ts};

    
};

void Sphere::calculate_hit(const BaseRay& incoming_ray, std::vector<BounceRay*>& return_ray) const{
    
    //testing
    //if (this->direction.x() )

    // Fin the ray to sphere vector and calculate the squared distance
    vector rs_vector = get_ray_sphere_vector(incoming_ray);
    double rs_squared = dot(rs_vector, rs_vector);

    // Stop if ray is inside sphere
    if (!is_outside(rs_squared, incoming_ray)) {
        return;
    }

    // Stop if ray points away from sphere
    vector tca_vec = incoming_ray.direction * dot(rs_vector, incoming_ray.direction) ;
    double tca = tca_vec.length();
    if (tca  <= 0) {
        return;
    }

    // Stop if ray misses sphere
    double hc_square = find_half_chord_distance(rs_squared, tca, incoming_ray);
    if (hc_square < 0) {
        return;
    }

    // Get intersection distance and calculate normal
    double inter_dist = find_intersection_distance(hc_square, tca);
    // std::cout << "intersection distance: " << inter_dist << '\n';
    BounceRay normal = find_intersection_normal(inter_dist, incoming_ray);
    // std::cout << "normal: \n";
    return_ray.push_back(new BounceRay{normal});
    return;
};