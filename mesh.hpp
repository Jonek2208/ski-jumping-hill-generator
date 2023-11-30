#pragma once

#include <vector>
#include <string>

#include "osj_math.hpp"

struct Mesh
{
    std::vector<osj::vec3> vertices;
    std::vector<osj::vec3> normals;
    std::vector<int> triangles;
    std::vector<osj::vec2> uvs;
    int subMeshCount;
    std::vector<int> &GetTriangles(int material) const;
};

struct Material
{
    std::string name;
};

struct MeshFilter
{
    Mesh *sharedMesh;
};
