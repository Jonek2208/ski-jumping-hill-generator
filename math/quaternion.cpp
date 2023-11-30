#include "quaternion.hpp"

namespace osj
{
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