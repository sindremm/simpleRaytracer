#ifndef RBASE_H
#define RBASE_H

#include "vec3.h"


class BaseRay {
    public:
        BaseRay();
        BaseRay(point pos, vector dir);
        point position;
        vector direction;
        
        void print() const;
};

#endif