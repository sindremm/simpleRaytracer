#ifndef CAM_H
#define CAM_H

#include "ray.h"
#include "sphere.h"
#include "environment.h"
#include "shader.h"


// sampling methods
enum class sample_method {
    single,
    five,
    jitter
};


class Camera : public Object {
    private:
        // camera spesifications
        double viewport_height = sqrt(3)/3;
        double viewport_width;
        double focal_length = 1.0; 
        double pixel_width;
        double pixel_heigth;
        int samples_per_pixel = 5;

        // ratio width / height
        double aspect_ratio;
        int image_width;
        int image_height;

        // Orientation of camera
        /*
        The camera image uses standard coordinates, with the x-axis increasing towards the right and the y-axis increasing upwards.
        Following the right-hand rule, the z-axis is then increasing "outwards" of the image towards the viewer. The z-axis is then
        imagined as the oposite of the camera direction
        */
        vector direction{0, 0, 1};
        vector x_axis{1, 0, 0};
        vector y_axis{0, 1, 0};



        sample_method current_method;

        // function implementations for the sampling_methods
        color single_sample_fill(vector x_coordinate, vector y_coordinate, Environment& env);
        color five_sample_fill(vector x_coordinate, vector y_coordinate, Environment& env);
        color jitter_sample_fill(vector x_coordinate, vector y_coordinate, Environment& env);

        // fill assigned pixel
        color fill_pixel(double pixel_x, double pixel_y, Environment& env);

        // take all objects hit by ray and find the first hit
        BounceRay* first_object_hit(const std::vector<BounceRay*>& result_normals);



    public:
        Camera(point pos, double a_ratio, double i_width);
        // temporary target argument for both shoot_rays and take_picture functions
        // change Object argument to environment and loop over every object in the sceene
        std::ostream& take_picture(std::ostream& output, Sphere& target);
        std::ostream& take_picture(std::ostream& output, Environment& env); 

        // get and set the sample method to be used for rendering
        sample_method get_sample_method() const { return current_method; };
        void set_sample_method(sample_method new_method) { current_method = new_method; };

        int get_samples_per_pixel() {return samples_per_pixel; };
        void set_samples_per_pixel(int new_amount) {samples_per_pixel = new_amount; };
};


#endif