
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

    Sphere sphere1{{1, 2,  10}, {50, 200, 200}, 5};
    Sphere sphere2{{3, 4, 5}, {100, 255, 40}, 2};

    Environment env; 
    env.add_hittable_object(&sphere1);
    env.add_hittable_object(&sphere2);

    // Create and output to file
    std::filebuf fb{};
    fb.open("C:\\Users\\47458\\Documents\\Programming\\simpleRayTracer\\out\\renders\\MultiTest.ppm", std::ios::out);
    std::ostream out{&fb};

    camera.set_sample_method(Camera::sample_method::jitter);
    camera.take_picture(out, env);

    fb.close();
    return 0;
}


