#include "hill_mesh.hpp"

Mesh generate_inrun_mesh(const Hill &hill)
{
    Mesh m;
    std::vector<double> lengths;

    auto inrun_points = hill.generate_inrun_points();

    lengths.push_back(0);
    for (size_t i = 1; i < inrun_points.size(); i++)
    {
        lengths.push_back(lengths[i - 1] + (inrun_points[i] - inrun_points[i - 1]).magnitude());
    }

    double b1 = hill.inrun_width();

    for (size_t i = 0; i < inrun_points.size(); i++)
    {
        m.vertices.emplace_back(inrun_points[i], -b1 / 2);
        m.vertices.emplace_back(inrun_points[i], b1 / 2);
        m.uvs.emplace_back(lengths[i], 0);
        m.uvs.emplace_back(lengths[i], b1);
    }

    for (size_t i = 0; i < inrun_points.size() - 1; i++)
    {
        m.triangles.emplace_back(2 * i + 0);
        m.triangles.emplace_back(2 * i + 3);
        m.triangles.emplace_back(2 * i + 1);
        m.triangles.emplace_back(2 * i + 0);
        m.triangles.emplace_back(2 * i + 2);
        m.triangles.emplace_back(2 * i + 3);
    }
    return m;
}

Mesh generate_lhill_mesh(const Hill &hill)
{
    Mesh mesh;

    auto lhill_points = hill.generate_lhill_points();

    for (size_t i = 0; i < lhill_points.size(); i++)
    {
        double half_w = hill.lhill_width(lhill_points[i].x) * 0.5;
        mesh.vertices.emplace_back(lhill_points[i].x, lhill_points[i].y, -half_w);
        mesh.uvs.emplace_back(i, -half_w);

        mesh.vertices.emplace_back(lhill_points[i].x, lhill_points[i].y, half_w);
        mesh.uvs.emplace_back(i, half_w);

        for (size_t i = 0; i < lhill_points.size() - 1; i++)
        {
            mesh.triangles.emplace_back(2 * i + 0);
            mesh.triangles.emplace_back(2 * i + 3);
            mesh.triangles.emplace_back(2 * i + 1);
            mesh.triangles.emplace_back(2 * i + 0);
            mesh.triangles.emplace_back(2 * i + 2);
            mesh.triangles.emplace_back(2 * i + 3);
        }
    }

    return mesh;
}