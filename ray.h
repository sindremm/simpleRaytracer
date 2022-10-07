#ifndef RAY_H
#define RAY_H

#include "raybase.h"
#include "object.h"

class Ray : public BaseRay{
    public:
        Ray();
        Ray(point pos, vector dir, const Object* src);
        const Object* source;

};


class BounceRay : public BaseRay{
    public:
        BounceRay(BaseRay& bRay, const VisibleObject* src);
        BounceRay(point pos, vector dir, const VisibleObject* src);
        const VisibleObject* source;
};


#endif