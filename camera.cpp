#include "camera.h"
#include <fstream>

Camera::Camera(point pos, double a_ratio, double i_width) : Object{pos}, aspect_ratio{a_ratio}, image_width{i_width} {
    image_height = static_cast<int>(i_width / a_ratio);
    viewport_width = a_ratio * viewport_height;

    // set the width and height of the pixels
    double pixel_width = viewport_width / image_width;
    double pixel_heigth = viewport_height / image_height;

}

color Camera::shoot_rays(double pixel_x, double pixel_y) {
    // transpose grid position to position in scene
    vector x_coordinate = x_axis * (image_width / 2) * pixel_width * pixel_x;
    vector y_coordinate = y_axis * (image_height / 2) * pixel_heigth * pixel_y;
    
    x_coordinate += x_axis * pixel_width/2;
    y_coordinate += y_axis * pixel_heigth/2;
    // Todo: Shoot several vectors randomly within one pixel

    // get pixel position
    vector pixel_position = x_coordinate + y_coordinate + direction;
    std::cout << "pixel at " << pixel_x << ", " << pixel_y << ": " << pixel_position << '\n';

    // Todo: create and shoot ray
    
    return color{0, 0, 0};

}


std::ostream& Camera::take_picture(std::ostream& output) {
    std::cout << "Starting rendering...\n";
    // setupt .ppm file
    output << "P3\n" << image_width << " " << image_height << "\n255\n";

    // iterate over each pixel from top left to bottom right
    const int max_p = 20;
    double percentage = static_cast<double>(max_p / image_height);
    for (int h = image_height - 1; h >= 0; h--) {
        int progress = static_cast<int>(percentage * h);
        std::cout << "\r progress: " << '[' << std::string(progress, '-') << std::string(max_p - progress, '-') << ']' << std::flush; 
        for (int w = 0; w < image_width; w++) {
            color pixel_color = shoot_rays(w, h);
        }

    }



}