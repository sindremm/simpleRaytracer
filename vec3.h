#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>
#include <array>


class vec3 : private std::array<double, 3> { 
    public:
        vec3() : std::array<double, 3>{} {this->fill(0.0); }; 
        vec3(double x, double y, double z) : std::array<double, 3>{} {this->at(0) = x; this->at(1) = y; this->at(2) = z;};


        double x() const { return this->at(0); };
        double y() const { return this->at(1); };
        double z() const { return this->at(2); };

        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);

        vec3& operator+=(const vec3 &v);
        vec3& operator*=(const double t);
        vec3& operator/=(const double t);

        friend std::ostream& operator<<(std::ostream& out, const vec3 &v);
        friend vec3 operator+(const vec3 &u, const vec3 &v);
        friend vec3 operator-(const vec3 &u, const vec3 &v);
        friend vec3 operator*(const vec3 &u, const vec3 &v);
        friend vec3 operator/(vec3 v, double t);
        friend double dot(const vec3 &u, const vec3 &v);
        friend vec3 cross(const vec3 &u, const vec3 &v);

        friend vec3 unit_vector(vec3 v);
        double length() const;
        double length_squared() const;

        void print() const;

        using std::array<double, 3>::begin;
        using std::array<double, 3>::end;
        using std::array<double, 3>::fill;
        using std::array<double, 3>::at;
};

using vector = vec3;
using point = vec3;
using color = vec3;


inline std::ostream& operator<<(std::ostream& out, const vec3 &v) {
    return out << v.x() << " " << v.y() << " " << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3{u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3{u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3{u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

inline vec3 operator*(const vec3 &v, double t) {
    return vec3{v.x() * t, v.y() * t, v.z() * t};
}

inline vec3 operator/(vec3 v, double t) {
    return v * (1/t);
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3{u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x()
    };
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif