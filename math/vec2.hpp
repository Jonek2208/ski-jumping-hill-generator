#pragma once
#include <ostream>
#include "math_utils.hpp"


namespace osj
{
    struct vec2
    {
        double x;
        double y;

        vec2(double _x = 0, double _y = 0) : x(_x), y(_y) {}

        double magnitude() const noexcept
        {
            return std::sqrt(x * x + y * y);
        }

        double sqr_magnitude() const noexcept
        {
            return x * x + y * y;
        }

        vec2 perp() const noexcept
        {
            return vec2{-y, x};
        }
    };

    std::ostream &operator<<(std::ostream &os, const vec2 &v) noexcept;
    vec2 operator+(const vec2 &a, const vec2 &b) noexcept;
    vec2 operator-(const vec2 &a, const vec2 &b) noexcept;
    vec2 operator-(const vec2 &a) noexcept;
    vec2 operator*(const vec2 &a, const vec2 &b) noexcept;
    vec2 operator*(const vec2 &a, double f) noexcept;
    vec2 operator/(const vec2 &a, double f) noexcept;
    vec2 operator*(double f, const vec2 &a) noexcept;
    double dot(const vec2 &a, const vec2 &b) noexcept;
    double cross(const vec2 &a, const vec2 &b) noexcept;

    vec2 from_degrees(double degrees) noexcept;
    vec2 from_radians(double radians) noexcept;
}