#include "camera.h"
#include <fstream>

Camera::Camera(point pos, double a_ratio, double i_width) : Object{pos}, aspect_ratio{a_ratio} {
    image_width = static_cast<int>(i_width);
    image_height = static_cast<int>(i_width / a_ratio);
    viewport_width = a_ratio * viewport_height;

    // set the width and height of the pixels
    pixel_width = viewport_width / image_width;
    pixel_heigth = viewport_height / image_height;
    std::cout << "pixel_width: " << pixel_width << "\n"
    << "pixel_height: " << pixel_heigth << "\n"
    << "image_width: " << image_width << "\n"
    << "image_height: " << image_height << "\n"
    << "viewport_width: " << viewport_width << "\n"
    << "viewport_height: " << viewport_height << "\n";

}

color Camera::shoot_rays(double pixel_x, double pixel_y, Sphere& target) {
    // transpose grid position to position in scene
    vector x_coordinate = x_axis * (- viewport_width / 2 + pixel_width * pixel_x);
    vector y_coordinate = y_axis * (viewport_height / 2 - pixel_heigth * pixel_y);

    // Center each ray on the assigned pixel
    x_coordinate += x_axis * pixel_width/2;
    y_coordinate += y_axis * pixel_heigth/2;

    // Todo: Shoot several vectors randomly within one pixel

    // get pixel position
    vector vector_to_pixel = unit_vector(x_coordinate + y_coordinate + direction * focal_length);

    // Todo: create and shoot ray
    Ray shooting_ray{position, vector_to_pixel, this};
    return shooting_ray.shoot(target);

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
            color pixel_color = shoot_rays(w, h, target);
            output << pixel_color.x() << " " << pixel_color.y() << " " << pixel_color.z() << "\n";
        }

    }

    return output;

}