#ifndef OBJ_H
#define OBJ_H

#include "vec3.h"

class Object {
    public:
        point position;

        Object(point pos);

};

class VisibleObject : public Object {
    public:
        VisibleObject(point pos, color col);
        color color_value;
};


#endif