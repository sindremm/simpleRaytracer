#include "object.h"

Object::Object(point pos) : position{pos} {}

HittableObject::HittableObject(point pos, color col) : Object{pos}, color_value{col} {}