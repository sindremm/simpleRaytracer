#include "camera.h"
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

color Camera::fill_pixel(double pixel_x, double pixel_y, Sphere& target) {
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
            result_color = single_sample_fill(x_coordinate, y_coordinate, target);
            break;
        }

        case sample_method::five: {
            result_color = five_sample_fill(x_coordinate, y_coordinate, target);
            break; 
        }

        case sample_method::jitter: {
            result_color = jitter_sample_fill(x_coordinate, y_coordinate, target);
            break;
        }
    };

    // get pixel position
    return result_color;

}


color Camera::single_sample_fill(vector x_coordinate, vector y_coordinate, Sphere& target_sphere) {
    vector vector_to_pixel = unit_vector(x_coordinate + y_coordinate + direction * focal_length);
    Ray shooting_ray{position, vector_to_pixel, this};

    return shooting_ray.shoot(target_sphere);
}

color Camera::five_sample_fill(vector x_coordinate, vector y_coordinate, Sphere& target_sphere) {
    // add middle ray
    color total_color = Ray{position, unit_vector(x_coordinate + y_coordinate + direction * focal_length), this}.shoot(target_sphere);

    // add two rays on each diagonal
    for (double w = -1; w <= 1; w += 2) {
        for (double h = -1; h <= 1; h += 2) {
            vector quadrant_vectors = unit_vector(vector{x_coordinate.x() + w * pixel_width/4 , y_coordinate.y() + h * pixel_heigth/4, direction.z()});
            Ray shoot_ray{position, quadrant_vectors, this};
            total_color += shoot_ray.shoot(target_sphere);
        }
    }

    // return the average color value
    return total_color/5; 
}

color Camera::jitter_sample_fill(vector x_coordinate, vector y_coordinate, Sphere& target_sphere) {
    color total_color;
    int total_samples = 30;
    for (int i = 0; i < total_samples; i++) {
        double random_x =  (static_cast<double>(rand()) / RAND_MAX) * pixel_width - pixel_width/2;
        double random_y = (static_cast<double>(rand()) / RAND_MAX) * pixel_heigth - pixel_heigth/2;

        // create random vector within pixel
        vector vec = unit_vector(vector{x_coordinate.x() + random_x, y_coordinate.y() + random_y, direction.z()});
        Ray shoot_ray{position, vec, this};
        total_color += shoot_ray.shoot(target_sphere);
    }

    return total_color/total_samples;
}


std::ostream& Camera::take_picture(std::ostream& output, Sphere& target) {
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
            color pixel_color = fill_pixel(w, h, target);
            output << pixel_color.x() << " " << pixel_color.y() << " " << pixel_color.z() << "\n";
        }

    }

    return output;

}