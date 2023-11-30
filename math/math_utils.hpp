#pragma once

#include <cmath>
namespace osj
{
    inline double deg2rad(double x) noexcept { return x * std::numbers::pi / 180.0; }
    inline double rad2deg(double x) noexcept { return x * 180.0 / std::numbers::pi; }
}