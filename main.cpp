#include <iostream>

#include "hills/hill_mesh.hpp"
#include "pugi/pugixml.hpp"

ProfileData parse_hill_node(const pugi::xml_node &hill_node)
{
    ProfileData pd;
    pd.name = hill_node.attribute("id").as_string();
    std::string profile_type = hill_node.attribute("profile-type").as_string();
    pd.type = (profile_type == "ICR2008" ? ProfileType::ICR2008 : (profile_type == "ICR1996" ? ProfileType::ICR1996 : ProfileType::ICR1992));

    auto inrun_node = hill_node.child("inrun");
    pd.gates = inrun_node.attribute("gates").as_int();
    pd.e = inrun_node.attribute("e").as_double();
    pd.es = inrun_node.attribute("es").as_double();
    pd.r1 = inrun_node.attribute("r1").as_double();
    pd.t = inrun_node.attribute("t").as_double();
    pd.gamma = inrun_node.attribute("gamma").as_double();
    pd.alpha = inrun_node.attribute("alpha").as_double();
    pd.b1 = inrun_node.attribute("b1").as_double();

    auto lhill_node = hill_node.child("landinghill");
    pd.w = lhill_node.attribute("w").as_double();
    pd.hS = lhill_node.attribute("hs").as_double();
    pd.h = lhill_node.attribute("h").as_double();
    pd.n = lhill_node.attribute("n").as_double();
    pd.s = lhill_node.attribute("s").as_double();
    pd.l1 = lhill_node.attribute("l1").as_double();
    pd.l2 = lhill_node.attribute("l2").as_double();
    pd.rL = lhill_node.attribute("rl").as_double();
    pd.r2L = lhill_node.attribute("r2l").as_double();
    pd.r2 = lhill_node.attribute("r2").as_double();
    pd.beta0 = lhill_node.attribute("beta0").as_double();
    pd.betaP = lhill_node.attribute("betap").as_double();
    pd.betaK = lhill_node.attribute("betak").as_double();
    pd.betaL = lhill_node.attribute("betal").as_double();
    pd.b2 = lhill_node.attribute("b2").as_double();
    pd.bK = lhill_node.attribute("bk").as_double();
    pd.bU = lhill_node.attribute("bu").as_double();

    auto outrun_node = hill_node.child("outrun");
    pd.a = outrun_node.attribute("a").as_double();
    pd.rA = outrun_node.attribute("ra").as_double();
    pd.betaA = outrun_node.attribute("betaa").as_double();

    return pd;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    const char *file_name = argv[1];
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name);

    if (!result)
        return -1;

    ProfileData pd = parse_hill_node(doc.child("hill"));
    Hill hill{pd};
    MeshExporter me;
    me << generate_inrun_mesh(hill) << generate_lhill_mesh(hill);
    me.write(std::cout);

    return 0;
}
