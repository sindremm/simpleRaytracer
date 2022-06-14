#ifndef VEC3_H
    #include "vec3.h"
#endif

#ifndef OBJ_H
#define OBJ_H



class Object {
    public:
        vec3 position;

        Object(vec3 pos);

};


class HittableObject : public Object {
    public:
        HittableObject(vec3 pos);

};


#endif