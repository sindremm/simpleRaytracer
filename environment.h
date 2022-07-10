#ifndef ENV_H
#define ENV_H

#include "object.h"
#include <vector>
class environment {
    public:

    private:
    std::vector<Object> scene_objects;
    std::vector<HittableObject> hittable_scene_objects;
        
};

#endif
