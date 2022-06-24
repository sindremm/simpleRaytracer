#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <iterator>



class vec3 {
    private:
        double e [3];
    
    public:
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);

        vec3& operator+=(const vec3 &v);
        vec3& operator*=(const double t);
        vec3& operator/=(const double t);

        double length() const;
        double lenght_squared() const;


};


// type aliases for vec3
using point3 = vec3;
using color = vec3;

#endif