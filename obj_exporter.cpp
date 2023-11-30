#include "obj_exporter.hpp"

void MeshToString(std::ostream &os, const Mesh &mesh)
{
    int numVertices = 0;
    std::vector<Material> mats;

    for (auto v : mesh.vertices)
    {
        ++numVertices;
        os << "v " << v.x << " " << v.y << " " << -v.z << "\n";
    }

    os << "\n";

    for (auto v : mesh.normals)
    {
        os << "vn " << -v.x << " " << -v.y << " " << v.z << "\n";
    }
    os << "\n";

    for (auto v : mesh.uvs)
    {
        os << "vt " << v.x << " " << v.y << "\n";
    }

    // for (size_t material = 0; material < m->subMeshCount; material++)
    // {
    // os << "usemtl " << mats[material].name << "\n";
    // os << "usemap " << mats[material].name << "\n";
    // }

    os << "\n";
    auto &triangles = mesh.triangles;
    
    for (size_t i = 0; i < triangles.size(); i += 3)
    {
        int tmp[] = {triangles[i] + 1, triangles[i + 1] + 1, triangles[i + 2] + 1};
        os << "f " << tmp[0] << "/" << tmp[0] << "/" << tmp[0] << " "
           << tmp[1] << "/" << tmp[1] << "/" << tmp[1] << " "
           << tmp[2] << "/" << tmp[2] << "/" << tmp[2] << "\n";
    }
}