#include "shader.h"

Shader::Shader() {}

Shader::~Shader() {
    for (BounceRay* ray : sample_rays) {
        delete ray;
    }
    return;
}

color Shader::calculate_color() {
    color total_color{};
    for (BounceRay* sample_ray : sample_rays) {
        if (sample_ray != nullptr) {
            total_color += sample_ray->source->color_value;
        } else {
            total_color += color{20, 20, 20};
        }
    }

    return total_color/sample_rays.size();

}

void Shader::add_sample_ray(BounceRay* new_ray) {
    sample_rays.push_back(new_ray);
    return;
}