#pragma once
#include "vec3.hpp"

namespace osj
{
    class Quaternion
    {
    private:
        double m_x, m_y, m_z, m_w;

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
        friend vec3 operator*(const Quaternion &q, const vec3 &v) noexcept;
    };

    const Quaternion identity_quaterion{0, 0, 0, 1};
    vec3 operator*(const Quaternion &q, const vec3 &v) noexcept;
}