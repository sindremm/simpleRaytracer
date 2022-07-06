#ifndef RAY_H
#include "ray.h"
#endif



#ifndef CAM_H
#define CAM_H
class Camera : public Object {
    public:
        Camera(point pos, double a_ratio, double i_width);
        // Orientation of camera
        /*
        The camera image uses standard coordinates, with the x-axis increasing towards the right and the y-axis increasing upwards.
        Following the right-hand rule, the z-axis is then increasing "outwards" of the image towards the viewer. The z-axis is then
        imagined as the oposite of the camera direction
        */
        vector direction{0, 0, 1};
        vector x_axis{1, 0, 0};
        vector y_axis{0, 1, 0};

        // ratio width / height
        double aspect_ratio;
        int image_width;
        int image_height;

        color shoot_rays(double pixel_x, double pixel_y);
        std::ostream& take_picture(std::ostream& output);

    private:
       double viewport_height = 2.0;
       double viewport_width;
       double focal_length = 1.0; 
       double pixel_width;
       double pixel_heigth;
};


#endif