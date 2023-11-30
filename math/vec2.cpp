#include "vec2.hpp"

namespace osj
{

    std::ostream &operator<<(std::ostream &os, const vec2 &v) noexcept
    {
        return (os << "(" << v.x << ", " << v.y << ")");
    }

    vec2 operator+(const vec2 &a, const vec2 &b) noexcept
    {
        return vec2{a.x + b.x,
                    a.y + b.y};
    }

    vec2 operator-(const vec2 &a, const vec2 &b) noexcept
    {
        return vec2{a.x - b.x,
                    a.y - b.y};
    }

    vec2 operator-(const vec2 &a) noexcept
    {
        return vec2{-a.x,
                    -a.y};
    }

    vec2 operator*(const vec2 &a, const vec2 &b) noexcept
    {
        return vec2{a.x * b.x,
                    a.y * b.y};
    }

    vec2 operator*(const vec2 &a, double f) noexcept
    {
        return vec2{a.x * f,
                    a.y * f};
    }

    vec2 operator/(const vec2 &a, double f) noexcept
    {
        return vec2{a.x / f,
                    a.y / f};
    }

    vec2 operator*(double f, const vec2 &a) noexcept
    {
        return vec2{a.x * f,
                    a.y * f};
    }

    double dot(const vec2 &a, const vec2 &b) noexcept
    {
        return a.x * b.x + a.y * b.y;
    }

    double cross(const vec2 &a, const vec2 &b) noexcept
    {
        return a.x * b.y - a.y * b.x;
    }

    vec2 from_degrees(double degrees) noexcept
    {
        double radians = deg2rad(degrees);
        return vec2{std::cos(radians), std::sin(radians)};
    }

    vec2 from_radians(double radians) noexcept
    {
        return vec2{std::cos(radians), std::sin(radians)};
    }
}