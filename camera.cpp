#include "camera.h"
#include "environment.h"

#include <fstream>
#include <random>
#include <time.h>
#include <math.h>

Camera::Camera(point pos, double a_ratio, double i_width) : Object{pos}, aspect_ratio{a_ratio} {
    image_width = static_cast<int>(i_width);
    image_height = static_cast<int>(i_width / a_ratio);
    viewport_width = a_ratio * viewport_height;

    // set the width and height of the pixels
    pixel_width = viewport_width / image_width;
    pixel_heigth = viewport_height / image_height;

    // set the standard sampling method
    current_method = sample_method::single;

    // Set seed for random generator
    srand(time(nullptr));
}

color Camera::fill_pixel(double pixel_x, double pixel_y, Environment& env) {
    /*
    Find the vector of the ray through the middle of the pixel and shoot
    rays with the selected sampling method
    */
    // transpose grid position to position in scene
    vector x_coordinate = x_axis * (- viewport_width / 2 + pixel_width * pixel_x);
    vector y_coordinate = y_axis * (viewport_height / 2 - pixel_heigth * pixel_y);

    // Center each ray on the assigned pixel
    x_coordinate += x_axis * pixel_width/2;
    y_coordinate += y_axis * pixel_heigth/2;

    color result_color;

    switch(current_method){
        case sample_method::single: {
            result_color = single_sample_fill(x_coordinate, y_coordinate, env);
            break;
        }

        case sample_method::five: {
            result_color = five_sample_fill(x_coordinate, y_coordinate, env);
            break; 
        }

        case sample_method::jitter: {
            result_color = jitter_sample_fill(x_coordinate, y_coordinate, env);
            break;
        }
    };

    // get pixel position
    return result_color;

}

BounceRay* Camera::first_object_hit(const std::vector<BounceRay*>& result_normals) {
    if (result_normals.size() == 0) {
        return nullptr;
    }

    BounceRay* closest_ray = result_normals.at(0);
    for (std::vector<BounceRay*>::const_iterator it = result_normals.begin(); it != result_normals.end(); ++it) {
        if (((*it)->position - position).length_squared() < (closest_ray->position - position).length_squared()) {
            closest_ray = *it;
        }
    }
    return closest_ray;
}

color Camera::single_sample_fill(vector x_coordinate, vector y_coordinate, Environment& env) {
    vector vector_to_pixel = unit_vector(x_coordinate + y_coordinate + direction * focal_length);
    Ray camera_ray{position, vector_to_pixel, this};

        // Add every object hit to vector
        std::vector<BounceRay*> hit_objects;
        for (auto a : env.get_hit_obj()) {
            a->calculate_hit(camera_ray, hit_objects);
        }

        BounceRay* closest_ray = first_object_hit(hit_objects);
        return closest_ray->source->color_value;
}

color Camera::five_sample_fill(vector x_coordinate, vector y_coordinate, Environment& env) {
    color total_color = color{};

    // add two rays on each diagonal
    for (double w = -1; w <= 1; w += 2) {
        for (double h = -1; h <= 1; h += 2) {
            vector quadrant_vectors = unit_vector(vector{x_coordinate.x() + w * pixel_width/4 , y_coordinate.y() + h * pixel_heigth/4, direction.z()});
            Ray camera_ray{position, quadrant_vectors, this};

            // Add every object hit to vector
            std::vector<BounceRay*> hit_objects;
            for (auto a : env.get_hit_obj()) {
                a->calculate_hit(camera_ray, hit_objects);
            }

            BounceRay* closest_ray = first_object_hit(hit_objects);
            total_color += closest_ray->source->color_value;
        }
    }

    // return the average color value
    return total_color/5; 
}

color Camera::jitter_sample_fill(vector x_coordinate, vector y_coordinate, Environment& env) {
    Shader pixel_shader;
    for (int i = 0; i < samples_per_pixel; i++) {
        double random_x =  (static_cast<double>(rand()) / RAND_MAX) * pixel_width - pixel_width/2;
        double random_y = (static_cast<double>(rand()) / RAND_MAX) * pixel_heigth - pixel_heigth/2;

        // create random vector within pixel
        vector vec = unit_vector(vector{x_coordinate.x() + random_x, y_coordinate.y() + random_y, direction.z()});
        Ray camera_ray{position, vec, this};

        // Add every object hit to vector
        std::vector<BounceRay*> hit_objects;
        for (auto a : env.get_hit_obj()) {
            a->calculate_hit(camera_ray, hit_objects);
        }

        pixel_shader.add_sample_ray(first_object_hit(hit_objects));

    }    
    
    return pixel_shader.calculate_color();
}

           

std::ostream& Camera::take_picture(std::ostream& output, Environment& env) {
    std::cout << "Starting rendering...\n";
    // setupt .ppm file
    output << "P3\n" << image_width << " " << image_height << "\n255\n";

    // iterate over each pixel from top left to bottom right
    const int max_p = 50;
    double percentage = static_cast<double>(max_p) / image_height;
    for (int h = image_height - 1; h >= 0; h--) {
        int progress = percentage * (image_height - h);
        std::cout << "\r progress: " << '[' << std::string(progress, '#') << std::string(max_p - progress, '-') << ']' << std::flush; 
        for (int w = 0; w < image_width; w++) {
            color pixel_color = fill_pixel(w, h, env);
            output << pixel_color.x() << " " << pixel_color.y() << " " << pixel_color.z() << "\n";
        }

    }

    return output;

}