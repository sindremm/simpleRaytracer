#ifndef ENV_H
#define ENV_H

#include "objecthit.h"
#include <vector>
class Environment {
    public:
        Environment();
        void add_scene_object(Object* obj);
        void add_hittable_object(HittableObject* hit_obj);
        void set_environment_color(color new_color);

        std::vector<Object*> get_obj() { return scene_objects; };
        std::vector<HittableObject*> get_hit_obj() { return hittable_objects; };
        color get_color();

    private:
        color environment_color{0, 0, 0};
        std::vector<Object*> scene_objects;
        std::vector<HittableObject*> hittable_objects;
        
};

#endif
