#ifndef VEC3_H
    #include "vec3.h"
#endif

#ifndef SPH_H
    #include "sphere.h"
#endif

#ifndef OBJ_H
    #include "object.h"
#endif


#ifndef RAY_H
#define RAY_H

class Ray : public Object{
    public:
        Ray();
        Ray(point pos, vector dir, Object* src);
        vector direction;
        Object* source;
        color shoot(Sphere& target_sphere);
        void print() const;

    private:

        vector get_ray_sphere_vector(Sphere target_sphere);
        bool is_outside(double rs_squared, Sphere target_sphere) const;
        double find_dot(vector rs_vector);
        double find_half_chord_distance(double rs_squared, double tca, Sphere& target_sphere) const;
        double find_intersection_distance(double hc_square, double tca) const;
        Ray find_intersection_normal(double intersection_distance, Sphere& target_sphere) const;
        


};


#endif