#include "vec3.h"

vec3 vec3::operator-() const {
    return vec3(-at(0), -at(1), -at(2));
}

double vec3::operator[](int i) const {
    return at(i);
}


double& vec3::operator[](int i) {
    return at(i);
}

vec3& vec3::operator+=(vec3 &v) {
    at(0) += v.x();
    at(1) += v.y();
    at(2) += v.z();
    return *this;
}

vec3& vec3::operator*=(const double t) {
    at(0) *= t;
    at(1) *= t;
    at(2) *= t;
    
    return *this;
}


vec3& vec3::operator/=(const double t) {
    return *this *= 1/t;
}


vec3 unit_vector(vec3 v) {
    return v / v.length();
}

double vec3::length() const {
    return std::sqrt(lenght_squared());
}

double vec3::lenght_squared() const {
    return at(0)*at(0) + at(1)*at(1) + at(2)*at(2);
}