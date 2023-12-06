#include "hills_map.hpp"

namespace osj
{
    const std::vector<MapHillData> &HillsMap::hills() const
    {
        return m_hills;
    }

    void HillsMap::add_hill(const MapHillData &map_hill_data)
    {
        m_hills.push_back(map_hill_data);
        const Hill &hill = map_hill_data.hill;

        m_ref_points.emplace(hill.name() + "/U", RefPoint{hill.name() + "/U", "", vec3(hill.point_U())}); 
        m_ref_points.emplace(hill.name() + "/T", RefPoint{hill.name() + "/T", "", vec3(hill.point_T())});
    }
}