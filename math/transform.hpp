#pragma once
#include "vec3.hpp"
#include "quaternion.hpp"

namespace osj
{
    struct Transform
    {
        vec3 localScale;
        vec3 localPosition;
        Quaternion localRotation;
        vec3 TransformPoint(const vec3 &v) const;
    };
}