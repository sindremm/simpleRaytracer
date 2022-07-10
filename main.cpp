
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
    
    Camera camera{{0, 0, 0}, 16.0 / 9.0, 400};

    Sphere sphere1{{0, 2,  10}, {255, 204, 102}, 5};
    Sphere sphere2{{1, 1, 5}, {100, 255, 40}, 2};

    // Create and output to file
    std::filebuf fb{};
    fb.open("out/renders/test1.ppm", std::ios::out);
    std::ostream out{&fb};

    camera.set_sample_method(Camera::sample_method::five);
    camera.take_picture(out, sphere1);

    fb.close();
    return 0;
}


