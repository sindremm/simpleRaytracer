#include "object.h"

Object::Object(point pos) : position{pos} {}


HittableObject::HittableObject(point pos) : Object{pos} {}