#pragma once

#include <cmath>
#include <ostream>

namespace osj
{
    inline double deg2rad(double x) noexcept { return x * std::numbers::pi / 180.0; }
    inline double rad2deg(double x) noexcept { return x * 180.0 / std::numbers::pi; }

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

    class Quaternion
    {
    private:
        double m_x, m_y, m_z, m_w;

    public:
        static const Quaternion identity;

    public:
        Quaternion(double x, double y, double z, double w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
        double x() const { return m_x; }
        double y() const { return m_y; }
        double z() const { return m_z; }
        double w() const { return m_w; }

        void set_x(double x) { m_x = x; }
        void set_y(double y) { m_y = y; }
        void set_z(double z) { m_z = z; }
        void set_w(double w) { m_w = w; }
        vec3 euler_angles() const;
        Quaternion inverse() const;
        friend vec3 operator*(const Quaternion &q, const vec3 &v) noexcept;
    };

    vec3 operator*(const Quaternion &q, const vec3 &v) noexcept;
}