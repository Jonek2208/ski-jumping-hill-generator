#pragma once
#include <ostream>
#include "math_utils.hpp"
#include "vec2.hpp"
namespace osj
{
    struct vec3
    {
        double x;
        double y;
        double z;

        vec3(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
        vec3(const vec2 &v, double _z = 0) : x(v.x), y(v.y), z(_z) {}
        operator vec2() const { return vec2{x, y}; }

        double sqr_magnitude() const noexcept { return x * x + y * y + z * z; }
        double magnitude() const noexcept { return std::sqrt(sqr_magnitude()); }
    };

    std::ostream &operator<<(std::ostream &os, const vec3 &v) noexcept;
    vec3 operator+(const vec3 &a, const vec3 &b) noexcept;
    vec3 operator-(const vec3 &a, const vec3 &b) noexcept;
    vec3 operator-(const vec3 &a) noexcept;
    vec3 operator*(const vec3 &a, const vec3 &b) noexcept;
    vec3 operator*(const vec3 &a, double f) noexcept;
    vec3 operator/(const vec3 &a, double f) noexcept;
    vec3 operator*(double f, const vec3 &a) noexcept;
    double dot(const vec3 &a, const vec3 &b) noexcept;
    vec3 cross(const vec3 &a, const vec3 &b) noexcept;
}