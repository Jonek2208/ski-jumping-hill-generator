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

    if (!result)
        return -1;

    osj::HillsMap hills_map = osj::parse_hills_map(doc);
    osj::MeshExporter me;
    for (const auto &it : hills_map.hills())
    {
        me << generate_inrun_mesh(it.hill, it.transform) << generate_lhill_mesh(it.hill, it.transform);
    }

    me.write(std::cout);

    return 0;
}
