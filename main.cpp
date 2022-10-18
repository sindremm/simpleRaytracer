
#include <iostream>
#include <fstream>

#include "camera.h"
#include "sphere.h"


template <typename T>
void test_pos(T f) {
        std::cout << typeid(f).name() << " position:\n" 
    << "\t x: " << f.position.x() << "\n"
    << "\t y: " << f.position.y() << "\n"
    << "\t z: " << f.position.z() << "\n";
}

template <typename T>
void test_dir(T f) {
        std::cout << typeid(f).name() << " direction:\n" 
    << "\t x: " << f.direction.x() << "\n"
    << "\t y: " << f.direction.y() << "\n"
    << "\t z: " << f.direction.z() << "\n";
}



int main() {
    
    Camera camera{{0, 0, 0}, 16.0 / 9.0, 1920};
    camera.set_samples_per_pixel(30);

    Sphere sphere1{{1, 0,  20}, {100, 200, 80}, 5};
    Sphere sphere2{{-2, 0, 15}, {75, 50, 200}, 2};

    Environment env; 
    env.add_hittable_object(&sphere1);
    env.add_hittable_object(&sphere2);
    env.set_environment_color({100, 100, 100});

    // Create and output to file
    std::filebuf fb{};
    fb.open("C:\\Users\\47458\\Documents\\Programming\\simpleRayTracer\\out\\renders\\testWithShader.ppm", std::ios::out);
    std::ostream out{&fb};

    camera.set_sample_method(sample_method::jitter);
    camera.take_picture(out, env);

    fb.close();
    return 0;
}


