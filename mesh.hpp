#pragma once

#include <vector>
#include "osj_math.hpp"

struct Mesh
{
    std::vector<osj::vec3> vertices;
    std::vector<osj::vec3> normals;
    std::vector<int> triangles;
    std::vector<osj::vec2> uvs;
};

class MeshExporter
{
private:
    int current_index = 0;
    std::vector<Mesh> meshes;
    void mesh2obj(std::ostream &os, const Mesh &mesh);

public:
    MeshExporter &operator<<(const Mesh &mesh);
    MeshExporter &operator<<(Mesh &&mesh);
    void write(std::ostream &os);
};