#include "osj_math.hpp"

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

    const Quaternion Quaternion::identity = Quaternion{0, 0, 0, 1};

    vec3 operator*(const Quaternion &rotation, const vec3 &point) noexcept
    {
        double x = rotation.m_x * 2;
        double y = rotation.m_y * 2;
        double z = rotation.m_z * 2;
        double xx = rotation.m_x * x;
        double xy = rotation.m_x * y;
        double xz = rotation.m_x * z;
        double yy = rotation.m_y * y;
        double yz = rotation.m_y * z;
        double zz = rotation.m_z * z;
        double wx = rotation.m_w * x;
        double wy = rotation.m_w * y;
        double wz = rotation.m_w * z;

        return vec3{(1 - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z,
                    (xy + wz) * point.x + (1 - (xx + zz)) * point.y + (yz - wx) * point.z,
                    (xz - wy) * point.x + (yz + wx) * point.y + (1 - (xx + yy)) * point.z};
    }
}