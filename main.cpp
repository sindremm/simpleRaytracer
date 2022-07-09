
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
    test_pos<Camera>(camera);

    Sphere sphere{{0, 0,  20}, {255, 0, 0}, 5};
    test_pos<Sphere>(sphere);

    // Create and output to file
    std::filebuf fb{};
    fb.open("/out/renders/test1.ppm", std::ios::out);
    std::ostream out{&fb};

    camera.take_picture(out, sphere);

    fb.close();
    return 0;
}


