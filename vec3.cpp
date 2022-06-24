#include "vec3.h"


vec3 vec3::operator-() const {
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int i) const {
    return e[i];
}


double& vec3::operator[](int i) {
    return e[i];
}


vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];

    return *this;
}

vec3& vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    
    return *this;
}

vec3& vec3::operator/=(const double t) {
    return *this *= 1/t;
}


double vec3::length() const {
    return std::sqrt(lenght_squared());
}

double vec3::lenght_squared() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}
