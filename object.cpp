#include "object.h"

Object::Object(vec3 pos) : position{pos} {}


HittableObject::HittableObject(vec3 pos) : Object{pos} {}