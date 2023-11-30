#pragma once
#include <string>
#include <vector>

#include "osj_math.hpp"
#include "mesh.hpp"




class ObjExporterScript
{
private:
    static int StartIndex;

public:
    static void Start()
    {
        StartIndex = 0;
    }
    static void End()
    {
        StartIndex = 0;
    }
};

void MeshToString(std::ostream &os, const Mesh &mesh);