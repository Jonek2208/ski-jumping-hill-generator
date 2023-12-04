#include "hill_xml.hpp"

namespace osj
{
    namespace xml
    {
        const char *const map = "map";
        const char *const hill = "hill";
        const char *const anchor = "anchor";
        const char *const inrun = "inrun";
        const char *const outrun = "outrun";
        const char *const landing_hill = "landing-hill";
        const char *const judges_tower = "judges-tower";
        const char *const profile_type = "profile-type";

        const char *const id = "id";
        const char *const ref_id = "ref-id";

        const char *const x = "x";
        const char *const y = "y";
        const char *const z = "z";
        const char *const sx = "sx";
        const char *const sy = "sy";
        const char *const sz = "sz";
        const char *const rx = "rx";
        const char *const ry = "ry";
        const char *const rz = "rz";

        const char *const gates = "gates";
        const char *const e = "e";
        const char *const es = "es";
        const char *const r1 = "r1";
        const char *const t = "t";
        const char *const gamma = "gamma";
        const char *const alpha = "alpha";

        const char *const b1 = "b1";
        const char *const b2 = "b2";
        const char *const bk = "bK";
        const char *const bu = "bU";

        const char *const w = "w";
        const char *const hs = "hs";
        const char *const h = "h";
        const char *const n = "n";
        const char *const s = "s";
        const char *const l1 = "l1";
        const char *const l2 = "l2";
        const char *const rl = "rL";
        const char *const r2l = "r2L";
        const char *const r2 = "r2";

        const char *const a = "a";
        const char *const ra = "rA";
        const char *const d = "d";
        const char *const q = "q";
        const char *const height = "height";

        const char *const beta0 = "beta0";
        const char *const betap = "betaP";
        const char *const betak = "betaK";
        const char *const betal = "betaL";
        const char *const betau = "betaU";
        const char *const betaa = "betaA";
    }

    ProfileData parse_hill_node(const pugi::xml_node &hill_node)
    {
        ProfileData pd;
        pd.name = hill_node.attribute(xml::id).as_string();
        pd.type = ProfileType(hill_node.attribute(xml::profile_type).as_int());
        auto inrun_node = hill_node.child(xml::inrun);
        pd.gates = inrun_node.attribute(xml::gates).as_int();
        pd.e = inrun_node.attribute(xml::e).as_double();
        pd.es = inrun_node.attribute(xml::es).as_double();
        pd.r1 = inrun_node.attribute(xml::r1).as_double();
        pd.t = inrun_node.attribute(xml::t).as_double();
        pd.gamma = inrun_node.attribute(xml::gamma).as_double();
        pd.alpha = inrun_node.attribute(xml::alpha).as_double();
        pd.b1 = inrun_node.attribute(xml::b1).as_double();

        auto lhill_node = hill_node.child(xml::landing_hill);
        pd.w = lhill_node.attribute(xml::w).as_double();
        pd.hS = lhill_node.attribute(xml::hs).as_double();
        pd.h = lhill_node.attribute(xml::h).as_double();
        pd.n = lhill_node.attribute(xml::n).as_double();
        pd.s = lhill_node.attribute(xml::s).as_double();
        pd.l1 = lhill_node.attribute(xml::l1).as_double();
        pd.l2 = lhill_node.attribute(xml::l2).as_double();
        pd.rL = lhill_node.attribute(xml::rl).as_double();
        pd.r2L = lhill_node.attribute(xml::r2l).as_double();
        pd.r2 = lhill_node.attribute(xml::r2).as_double();
        pd.beta0 = lhill_node.attribute(xml::beta0).as_double();
        pd.betaP = lhill_node.attribute(xml::betap).as_double();
        pd.betaK = lhill_node.attribute(xml::betak).as_double();
        pd.betaL = lhill_node.attribute(xml::betal).as_double();
        pd.b2 = lhill_node.attribute(xml::b2).as_double();
        pd.bK = lhill_node.attribute(xml::bk).as_double();
        pd.bU = lhill_node.attribute(xml::bu).as_double();

        auto outrun_node = hill_node.child(xml::outrun);
        pd.a = outrun_node.attribute(xml::a).as_double();
        pd.rA = outrun_node.attribute(xml::ra).as_double();
        pd.betaA = outrun_node.attribute(xml::betaa).as_double();

        return pd;
    }

    vec3 parse_position(const pugi::xml_node &node)
    {
        return vec3{node.attribute(xml::x).as_double(),
                    node.attribute(xml::y).as_double(),
                    node.attribute(xml::z).as_double()};
    }

    vec3 parse_rotation(const pugi::xml_node &node)
    {
        return vec3{node.attribute(xml::rx).as_double(),
                    node.attribute(xml::ry).as_double(),
                    node.attribute(xml::rz).as_double()};
    }

    vec3 parse_scale(const pugi::xml_node &node)
    {
        return vec3{node.attribute(xml::sx).as_double(1),
                    node.attribute(xml::sy).as_double(1),
                    node.attribute(xml::sz).as_double(1)};
    }

    // RefPoint parse_ref_point(const pugi::xml_node &node)
    // {
    //     RefPoint res;
    // }
}