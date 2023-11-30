#include "hill_mesh.hpp"
#include "mesh.hpp"

void GenerateInrunCollider(const Hill &hill, double b1)
{
    Mesh m;
    std::vector<double> lengths;

    auto inrun_points = hill.GenerateInrunPoints();
    m.vertices.reserve(inrun_points.size() * 2);
    m.uvs.reserve(inrun_points.size() * 2);
    m.triangles.reserve((inrun_points.size() - 1) * 6);
    lengths.reserve(inrun_points.size());

    lengths.push_back(0);
    for (size_t i = 1; i < inrun_points.size(); i++)
    {
        lengths.push_back(lengths[i - 1] + (inrun_points[i] - inrun_points[i - 1]).magnitude());
    }

    for (size_t i = 0; i < inrun_points.size(); i++)
    {
        m.vertices.emplace_back(inrun_points[i] -b1 / 2);
        m.vertices.emplace_back(inrun_points[i], b1 / 2);
        m.uvs.emplace_back(lengths[i], -b1);
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
}

/*
void GenerateLandingAreaCollider()
{
    var verticesList = new List<Vector3>();
    var uvsList = new List<Vector2>();
    var facesList = new List<(int, int, int, int)>();

    var b = new float[hill.landingAreaPoints.Length];

    for (var i = 0; i < hill.landingAreaPoints.Length; i++)
    {
        b[i] = hill.landingAreaPoints[i].x <= hill.K.x
                   ? (profileData.Value.b2 / 2) + hill.landingAreaPoints[i].x / hill.K.x *
                                                      ((profileData.Value.bK - profileData.Value.b2) / 2)
               : hill.landingAreaPoints[i].x >= hill.U.x
                   ? (profileData.Value.bU / 2)
                   : (profileData.Value.bK / 2) + (hill.landingAreaPoints[i].x - hill.K.x) /
                                                      (hill.U.x - hill.K.x) * ((profileData.Value.bU - profileData.Value.bK) / 2);
    }

    for (var i = 0; i < hill.landingAreaPoints.Length; i++)
    {
        verticesList.Add(new Vector3(hill.landingAreaPoints[i].x, hill.landingAreaPoints[i].y, -b[i]));
        uvsList.Add(new Vector2(i, -b[i]));

        verticesList.Add(new Vector3(hill.landingAreaPoints[i].x, hill.landingAreaPoints[i].y, b[i]));
        uvsList.Add(new Vector2(i, b[i]));

        if (i > 0)
        {
            var x = verticesList.Count;
            facesList.Add((x - 4, x - 3, x - 2, x - 1));
        }
    }

    mesh.vertices = verticesList.ToArray();
    mesh.triangles = MeshFunctions.FacesToTriangles(facesList);
    mesh.uv = uvsList.ToArray();
    landingArea.gObj.GetComponent<MeshCollider>().sharedMesh = mesh;
}*/