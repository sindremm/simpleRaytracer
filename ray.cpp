#include "ray.h"
#include "environment.h"
#include <cmath>
#include <vector>
#include <numeric>


BaseRay::BaseRay() : position{0, 0, 0}, direction{0, 0, 0} {}

BaseRay::BaseRay(point pos, vector dir) : position{pos}, direction{dir} {}


Ray::Ray() : BaseRay{{0, 0, 0}, {0, 0, 0}}, source{NULL} {}

Ray::Ray(point pos, vector dir, const Object* src) : BaseRay{pos, dir}, source{src} {}


BounceRay::BounceRay(point pos, vector dir, const VisibleObject* src) : BaseRay{pos, dir}, source{src} {}
