#pragma once

#include "hill.hpp"
#include "mesh.hpp"

namespace osj
{
    Mesh generate_inrun_mesh(const Hill &hill);
    Mesh generate_lhill_mesh(const Hill &hill);
}