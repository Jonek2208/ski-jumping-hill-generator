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

    Quaternion::Quaternion(vec3 _euler_angles)
    {
        double cx = std::cos(deg2rad(_euler_angles.x) * 0.5);
        double sx = std::sin(deg2rad(_euler_angles.x) * 0.5);
        double cy = std::cos(deg2rad(_euler_angles.y) * 0.5);
        double sy = std::sin(deg2rad(_euler_angles.y) * 0.5);
        double cz = std::cos(deg2rad(_euler_angles.z) * 0.5);
        double sz = std::sin(deg2rad(_euler_angles.z) * 0.5);
        m_w = cx * cy * cz + sx * sy * sz;
        m_x = sx * cy * cz - cx * sy * sz;
        m_y = cx * sy * cz + sx * cy * sz;
        m_z = cx * cy * sz - sx * sy * cz;
    }

    vec3 Quaternion::euler_angles() const
    {
        double sx_cy = 2 * (m_w * m_x + m_y * m_z);
        double cx_cy = 1 - 2 * (m_x * m_x + m_y * m_y);

        double sx = std::sqrt(1 + 2 * (m_w * m_y - m_x * m_z));
        double cx = std::sqrt(1 - 2 * (m_w * m_y - m_x * m_z));

        double sz_cy = 2 * (m_w * m_z + m_x * m_y);
        double cz_cy = 1 - 2 * (m_y * m_y + m_z * m_z);

        return vec3(rad2deg(std::atan2(sx_cy, cx_cy)),
                    rad2deg(2 * std::atan2(sx, cx) - std::numbers::pi * 0.5),
                    rad2deg(std::atan2(sz_cy, cz_cy)));
    }

    Quaternion Quaternion::inverse() const
    {
        return {m_w, -m_x, -m_y, -m_z};
    }

    const Quaternion Quaternion::identity = Quaternion{1, 0, 0, 0};

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

    Quaternion operator*(const Quaternion &r, const Quaternion &s) noexcept
    {
        return Quaternion(
            r.m_w * s.m_w - r.m_x * s.m_x - r.m_y * s.m_y - r.m_z * s.m_z,
            r.m_w * s.m_x + r.m_x * s.m_w - r.m_y * s.m_z + r.m_z * s.m_y,
            r.m_w * s.m_y + r.m_x * s.m_z + r.m_y * s.m_w - r.m_z * s.m_x,
            r.m_w * s.m_z - r.m_x * s.m_y + r.m_y * s.m_x - r.m_z * s.m_w);
    }

    Transform operator*(const Transform &parent, const Transform &t)
    {
        return Transform(parent.position + parent.rotation * (parent.scale * t.position),
                         parent.rotation * t.rotation,
                         parent.scale * t.scale);
    }

    std::ostream &operator<<(std::ostream &os, const Quaternion &q) noexcept
    {
        os << "(" << q.m_x << ", " << q.m_y << "," << q.m_z << ", " << q.m_w << ")";
        return os;
    }

    Transform::Transform(vec3 _pos, Quaternion _rot, vec3 _scale) : position(_pos), rotation(_rot), scale(_scale) {}
    Transform::Transform(vec3 _pos, vec3 _euler_rot, vec3 _scale) : position(_pos), rotation(_euler_rot), scale(_scale) {}

    const Transform Transform::identity = {vec3(0, 0, 0), Quaternion::identity, vec3(1, 1, 1)};

    Transform Transform::inverse() const
    {
        return {-position, rotation.inverse(), -scale};
    }

    vec3 Transform::transform_point(const vec3 &v) const
    {
        return rotation * (scale * v) + position;
    }
}