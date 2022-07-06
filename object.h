#ifndef VEC3_H
    #include "vec3.h"
#endif

#ifndef OBJ_H
#define OBJ_H



class Object {
    public:
        point position;

        Object(point pos);

};


class HittableObject : public Object {
    public:
        HittableObject(point pos, color col);
        color color_value;

};


#endif