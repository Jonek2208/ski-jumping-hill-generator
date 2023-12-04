#include "hill_mesh.hpp"

namespace osj
{
    Mesh generate_inrun_mesh(const Hill &hill)
    {
        auto inrun_points = hill.generate_inrun_points();

        Mesh mesh{"inrun"};
        mesh.vertices.reserve(inrun_points.size() * 2);
        mesh.uvs.reserve(inrun_points.size() * 2);
        mesh.triangles.reserve((inrun_points.size() - 1) * 6);

        std::vector<double> lengths(inrun_points.size());
        lengths[0] = 0;
        for (size_t i = 1; i < inrun_points.size(); i++)
        {
            lengths[i] = lengths[i - 1] + (inrun_points[i] - inrun_points[i - 1]).magnitude();
        }

        double b1 = hill.inrun_width();

        for (size_t i = 0; i < inrun_points.size(); i++)
        {
            mesh.vertices.emplace_back(inrun_points[i], -b1 / 2);
            mesh.vertices.emplace_back(inrun_points[i], b1 / 2);
            mesh.uvs.emplace_back(lengths[i], 0);
            mesh.uvs.emplace_back(lengths[i], b1);
        }

        for (size_t i = 0; i < inrun_points.size() - 1; i++)
        {
            mesh.triangles.emplace_back(2 * i + 0);
            mesh.triangles.emplace_back(2 * i + 3);
            mesh.triangles.emplace_back(2 * i + 1);
            mesh.triangles.emplace_back(2 * i + 0);
            mesh.triangles.emplace_back(2 * i + 2);
            mesh.triangles.emplace_back(2 * i + 3);
        }
        return mesh;
    }

    Mesh generate_lhill_mesh(const Hill &hill)
    {
        auto lhill_points = hill.generate_lhill_points();
        Mesh mesh{"lhill"};
        mesh.vertices.reserve(lhill_points.size() * 2);
        mesh.uvs.reserve(lhill_points.size() * 2);
        mesh.triangles.reserve((lhill_points.size() - 1) * 6);

        for (size_t i = 0; i < lhill_points.size(); i++)
        {
            double half_w = hill.lhill_width(lhill_points[i].x) * 0.5;
            mesh.vertices.emplace_back(lhill_points[i].x, lhill_points[i].y, -half_w);
            mesh.uvs.emplace_back(i, -half_w);

            mesh.vertices.emplace_back(lhill_points[i].x, lhill_points[i].y, half_w);
            mesh.uvs.emplace_back(i, half_w);
        }

        for (size_t i = 0; i < lhill_points.size() - 1; i++)
        {
            mesh.triangles.emplace_back(2 * i + 0);
            mesh.triangles.emplace_back(2 * i + 3);
            mesh.triangles.emplace_back(2 * i + 1);
            mesh.triangles.emplace_back(2 * i + 0);
            mesh.triangles.emplace_back(2 * i + 2);
            mesh.triangles.emplace_back(2 * i + 3);
        }

        return mesh;
    }
}