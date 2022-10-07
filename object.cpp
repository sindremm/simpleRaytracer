#include "object.h"

Object::Object(point pos) : position{pos} {}

VisibleObject::VisibleObject(point pos, color col) : Object{pos}, color_value{col} {}

/*
void HittableObject::targeted(const Ray& incoming_ray, color& result_color) const {
    if (!check_hit(incoming_ray)) {
        result_color = calculate_hit(incoming_ray);
    }
    return;
}
*/