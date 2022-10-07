#ifndef OBJH_H
#define OBJH_H

#include "ray.h"
class HittableObject : public VisibleObject {
    public:
        HittableObject(point pos, color col);
        virtual void calculate_hit(const BaseRay& incoming_ray, std::vector<BounceRay*>& return_ray) const = 0;

};

#endif