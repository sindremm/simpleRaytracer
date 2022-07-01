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
        Ray(vec3 pos, vec3 dir, Object* src);
        vec3 direction;
        Object* source;
        void normalize();
    private:

        vec3 get_ray_sphere_vector(Sphere target_sphere);
        bool is_outside(double rs_squared, Sphere target_sphere) const;
        double calculate_tca(vec3 rs_vector);
        double calculate_hc_square(double rs_squared, double tca, Sphere& target_sphere) const;
        double isect_dist(double hc_square, double tca) const;
        Ray intersection_normal(double intersection_distance, Sphere& target_sphere) const;
        


};


#endif