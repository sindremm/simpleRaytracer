
#include <iostream>

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
    

    Object a{{1, 2, 3}};
    test_pos<Object>(a);

    Ray b{{0, 0, 0}, {1, 0, 0}, &a};
    test_pos<Ray>(b);
    test_dir<Ray>(b);

    b.normalize();
    test_dir<Ray>(b);

    Camera c{{0, 0, 0}, {1, 0, 0}};
    test_pos<Ray>(c);
    test_dir<Ray>(c);

    Sphere s{{10, 0, 0}, 5};
    test_pos<Sphere>(s);
    std::cout << "radius: " << s.radius << " squared: " << s.radius_squared << '\n'; 
    
    b.shoot(s);
    /*
    nvec3 nv{};
    std::cout << "nv:\n";
    for (auto n : nv) {
        std::cout << n << '\n';
    }    

    nvec3 nv2{1.1, 2.2, 3.3};
    std::cout << "nv2:\n";
    for (auto n : nv2) {
        std::cout << n << '\n';
    }    
    */

    return 0;
}


