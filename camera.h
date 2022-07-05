#ifndef RAY_H
#include "ray.h"
#endif



#ifndef CAM_H
#define CAM_H
class Camera : public Ray {
    public:
        Camera(point pos, vector dir);
};


#endif