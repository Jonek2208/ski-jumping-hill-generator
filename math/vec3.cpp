#include "vec3.hpp"

namespace osj
{

    std::ostream &operator<<(std::ostream &os, const vec3 &v) noexcept
    {
        return (os << "(" << v.x << ", " << v.y << ", " << v.z << ")");
    }

    vec3 operator+(const vec3 &a, const vec3 &b) noexcept
    {
        return vec3{a.x + b.x,
                    a.y + b.y,
                    a.z + b.z};
    }

    vec3 operator-(const vec3 &a, const vec3 &b) noexcept
    {
        return vec3{a.x - b.x,
                    a.y - b.y,
                    a.z - b.z};
    }

    vec3 operator-(const vec3 &a) noexcept
    {
        return vec3{-a.x,
                    -a.y,
                    -a.z};
    }

    vec3 operator*(const vec3 &a, const vec3 &b) noexcept
    {
        return vec3{a.x * b.x,
                    a.y * b.y,
                    a.z * b.z};
    }

    vec3 operator*(const vec3 &a, double f) noexcept
    {
        return vec3{f * a.x,
                    f * a.y,
                    f * a.z};
    }

    vec3 operator/(const vec3 &a, double f) noexcept
    {
        return vec3{a.x / f,
                    a.y / f,
                    a.z / f};
    }

    vec3 operator*(double f, const vec3 &a) noexcept
    {
        return vec3{f * a.x,
                    f * a.y,
                    f * a.z};
    }

    double dot(const vec3 &a, const vec3 &b) noexcept
    {
        return a.x * b.x + a.y * b.y;
    }

    vec3 cross(const vec3 &a, const vec3 &b) noexcept
    {
        return vec3{a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x};
    }
}