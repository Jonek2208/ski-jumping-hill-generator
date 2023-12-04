#include <iostream>

#include "hill_xml.hpp"
#include "hill_mesh.hpp"
#include "pugi/pugixml.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    const char *file_name = argv[1];
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file_name);
    auto map_node = doc.child(osj::xml::map);

    if (!result)
        return -1;

    osj::ProfileData pd = osj::parse_hill_node(map_node.child(osj::xml::hill));
    osj::Hill hill{pd};
    osj::MeshExporter me;
    me << generate_inrun_mesh(hill) << generate_lhill_mesh(hill);
    me.write(std::cout);

    return 0;
}
