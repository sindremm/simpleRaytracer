#ifndef SPH_H
#define SPH_H

#include "objecthit.h"
#include "raybase.h"

class Sphere : public HittableObject {
    public:
        Sphere(point sphere_center, color sphere_color, double sphere_radius);
        double radius;
        double radius_squared;
        void calculate_hit(const BaseRay& incoming_ray, std::vector<BounceRay*>& return_ray) const override;

    private:

        vector get_ray_sphere_vector(const BaseRay& incoming_ray) const;
        bool is_outside(double rs_squared, const BaseRay& incoming_ray) const;
        double find_dot(vector rs_vector, const BaseRay& incoming_ray) ;
        double find_half_chord_distance(double rs_squared, double tca, const BaseRay& incoming_ray) const;
        double find_intersection_distance(double hc_square, double tca) const;
        BounceRay find_intersection_normal(double intersection_distance, const BaseRay& incoming_ray) const;
};

#endif
