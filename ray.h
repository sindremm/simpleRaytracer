#ifndef VEC3_H
    #include "vec3.h"
#endif

#ifndef OBJ_H
    #include "object.h"
#endif


#ifndef RAY_H
#define RAY_H

class Ray : public Object{
    public:
        Ray(vec3 pos, vec3 dir);
        vec3 direction;
        void normalize();
    private:
        


};

#endif