#include "environment.h"

Environment::Environment() {};

void Environment::add_scene_object(Object* obj) {
    scene_objects.push_back(obj);
    return;
}

void Environment::add_hittable_object(HittableObject* hit_obj) {
    hittable_objects.push_back(hit_obj);
    return;
}

void Environment::set_environment_color(color new_color) {
    environment_color = new_color;
}


color Environment::get_color() {
    return environment_color;
}

