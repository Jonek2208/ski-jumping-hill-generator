#pragma once
#include <cmath>

#include "pugi/pugixml.hpp"
#include "hill.hpp"

namespace osj
{
    namespace xml
    {
        extern const char *const map;
        extern const char *const hill;
        extern const char *const anchor;
        extern const char *const inrun;
        extern const char *const outrun;
        extern const char *const landing_hill;
        extern const char *const judges_tower;
        extern const char *const profile_type;

        extern const char *const id;
        extern const char *const ref_id;

        extern const char *const x;
        extern const char *const y;
        extern const char *const z;
        extern const char *const sx;
        extern const char *const sy;
        extern const char *const sz;
        extern const char *const rx;
        extern const char *const ry;
        extern const char *const rz;

        extern const char *const gates;
        extern const char *const e;
        extern const char *const es;
        extern const char *const r1;
        extern const char *const t;
        extern const char *const gamma;
        extern const char *const alpha;

        extern const char *const b1;
        extern const char *const b2;
        extern const char *const bk;
        extern const char *const bu;

        extern const char *const w;
        extern const char *const hs;
        extern const char *const h;
        extern const char *const n;
        extern const char *const s;
        extern const char *const l1;
        extern const char *const l2;
        extern const char *const rl;
        extern const char *const r2l;
        extern const char *const r2;

        extern const char *const a;
        extern const char *const ra;
        extern const char *const d;
        extern const char *const q;
        extern const char *const height;

        extern const char *const beta0;
        extern const char *const betap;
        extern const char *const betak;
        extern const char *const betal;
        extern const char *const betau;
        extern const char *const betaa;
    }

    ProfileData parse_hill_node(const pugi::xml_node &hill_node);
    vec3 parse_position(const pugi::xml_node &node);
    vec3 parse_rotation(const pugi::xml_node &node);
    vec3 parse_scale(const pugi::xml_node &node);

    struct SerializableTransform
    {
        vec3 position;
        Quaternion rotation;
        vec3 scale;

        vec3 euler_angles() const { return rotation.euler_angles(); }

        SerializableTransform inverse() const
        {
            return {-position, rotation.inverse(), -scale};
        }
    };

    struct RefPoint
    {
        std::string id;
        std::string referenceId;
        SerializableTransform value;
        std::vector<RefPoint *> auxiliaryRefs; 
    };

    struct MapHillData
    {
        RefPoint anchor;
        RefPoint ref_transform;
        ProfileData profile_data;
    };
}