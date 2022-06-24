#ifndef OBJ_H
    #include "object.h"
#endif


#ifndef SPH_H
#define SPH_H

class Sphere : public HittableObject {
    public:
        Sphere(vec3 sphere_center, double sphere_radius);
        double radius;
        double radius_squared;
};

#endif