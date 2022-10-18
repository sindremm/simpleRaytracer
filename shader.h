#ifndef SHADER_H
#define SHADER_H

#include "vec3.h"
#include "ray.h"

class Shader {
    public:
        enum shading {
            normal
        };

        Shader();
        ~Shader();

        color calculate_color();
        void set_shading_type();
        void add_sample_ray(BounceRay* new_ray);
        std::vector<BounceRay> get_sample_rays();

    private:
        shading shading_type;
        std::vector<BounceRay*> sample_rays;
};

#endif