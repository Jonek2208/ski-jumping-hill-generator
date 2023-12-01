#include "mesh.hpp"
#include <iostream>

void MeshExporter::mesh2obj(std::ostream &os, const Mesh &mesh)
{
    for (auto v : mesh.vertices)
    {
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

    os << "\n";
    auto &triangles = mesh.triangles;

    for (size_t i = 0; i < triangles.size(); i += 3)
    {
        int tmp[] = {triangles[i] + 1 + current_index, triangles[i + 1] + 1 + current_index, triangles[i + 2] + 1 + current_index};
        os << "f " << tmp[0] << "/" << tmp[0] << "/" << tmp[0] << " "
           << tmp[1] << "/" << tmp[1] << "/" << tmp[1] << " "
           << tmp[2] << "/" << tmp[2] << "/" << tmp[2] << "\n";
    }

    current_index += mesh.vertices.size();
}

MeshExporter &MeshExporter::operator<<(const Mesh &mesh)
{
    meshes.emplace_back(mesh);
    return *this;
}

MeshExporter &MeshExporter::operator<<(Mesh &&mesh)
{
    meshes.emplace_back(std::move(mesh));
    return *this;
}

void MeshExporter::write(std::ostream &os)
{
    for (const auto &mesh : meshes)
    {
        mesh2obj(os, mesh);
    }
}
