#include <iostream>

#include "map_fetcher.h"
#include "utils.h"
#include "lib/pugixml/pugixml.hpp"

map_fetcher::map_fetcher(double south, double west, double north, double east) :
    site("overpass-api.de/api/interpreter?data=")
{
    // map_fetcher requete("overpass-api.de/api/interpreter?data=", "way(50.746,7.154,50.748,7.157);(._;>;);out body;");
    site_path = "way(" + stringify(south) + ","
                       + stringify(west) + ","
                       + stringify(north) + ","
                       + stringify(east) + ");(._;>;);out body;";
    url_encode();
}

// From https://code.google.com/p/twitcurl/source/browse/trunk/libtwitcurl/urlencode.cpp?r=47
void map_fetcher::url_encode()
{
    std::string c(site_path);
    std::string escaped;
    unsigned long max = c.size();
    for(auto i(0); i < max; i++)
    {
        if ( (48 <= c[i] && c[i] <= 57) ||//0-9
             (65 <= c[i] && c[i] <= 90) ||//ABC...XYZ
             (97 <= c[i] && c[i] <= 122) || //abc...xyz
             (c[i]=='~' || c[i]=='-' || c[i]=='_' || c[i]=='.')
           )
        {
            escaped.append(&c[i], 1);
        }
        else
        {
            escaped.append("%");
            escaped.append(char2hex(c[i]));//converts char 255 to string "FF"
        }
    }
    request = site + escaped;
}

void map_fetcher::execute()
{
    //response = send_request(request.c_str());
    //parse_response();
}

// http://pugixml.org
void map_fetcher::parse_response()
{
    // Load the response to pugixml
    pugi::xml_document doc;
    auto res = doc.load(response.c_str());

    // If we have an error or the selected map is empty
    if (!res) return;

    // The structure where all info is
    pugi::xml_node osm = doc.child("osm");

    // Get all nodes
    for (pugi::xml_node inode: osm.children("node"))
    {
        nodes.insert(std::pair<map_node::node_id, map_node>(
                         atol(inode.attribute("id").value()),
                         map_node(atof(inode.attribute("lon").value()),
                              atof(inode.attribute("lat").value()))));
    }

    // Get all ways
    for (pugi::xml_node inode: osm.children("way"))
    {
        std::vector<map_node::node_id> way_nodes;
        std::map<std::string, std::string> way_attributes;

        for (pugi::xml_node nd: inode.children("nd"))
        {
            way_nodes.push_back(map_node::node_id(atof(nd.attribute("ref").value())));
        }

        for (pugi::xml_node tag: inode.children("tag"))
        {
            way_attributes.insert(
                        std::pair<std::string, std::string>(
                            tag.attribute("k").value(),
                            tag.attribute("v").value()));
        }

        ways.push_back(map_way(map_way::way_id(atol(inode.attribute("id").value())),
                           way_nodes,
                           way_attributes));
    }
}

void map_fetcher::print_response()
{
    std::cout << response << std::endl << response.size() << std::endl;
}

void map_fetcher::print()
{
    using std::cout;
    using std::endl;

    for(auto it = ways.begin(); it != ways.end(); ++it)
    {
        cout << "- Way (" << it->id << ")--------------\nNodes ::\nbegin -> ";
        for(auto itt = it->path.begin(); itt != it->path.end(); ++itt)
        {
            cout << *itt << " -> ";
        }
        cout << "end" << endl << "Attributes ::\n";
        for(auto itt = it->attributes.begin(); itt != it->attributes.end(); ++itt)
        {
            cout << itt->first << " = " << itt->second << endl;
        }
    }
}

std::vector<map_way> map_fetcher::get_ways()
{
    return ways;
}

std::map<map_node::node_id, map_node> map_fetcher::get_nodes()
{
    return nodes;
}
