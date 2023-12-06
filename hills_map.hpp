#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "hill.hpp"

namespace osj
{

    struct RefPoint
    {
        std::string id;
        std::string referenceId;
        Transform value;
        // std::vector<RefPoint> auxiliaryRefs;
        RefPoint(std::string _id, std::string _ref_id, vec3 _pos) : id(_id), referenceId(_ref_id), value(_pos, Quaternion::identity, {1, 1, 1}) {}
        RefPoint(std::string _id, std::string _ref_id, Transform _t) : id(_id), referenceId(_ref_id), value(_t) {}
        RefPoint(const RefPoint &r) = default;
        RefPoint &operator=(const RefPoint &r) = default;
        RefPoint(RefPoint &&r) = default;
        RefPoint &operator=(RefPoint &&r) = default;
    };

    struct MapHillData
    {
        Hill hill;
        Transform transform;
        RefPoint anchor;
        MapHillData(Hill _hill, Transform _transform, RefPoint _anchor) : hill(_hill), transform(_transform), anchor(_anchor) {}
    };

    class HillsMap
    {
    private:
        std::vector<MapHillData> m_hills;
        std::unordered_map<std::string, RefPoint> m_ref_points;

    public:
        const std::vector<MapHillData> &hills() const;
        void add_hill(const MapHillData &map_hill_data);
    };
}