#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "trajectory_utilities.hpp"

namespace bg = boost::geometry;

int main()
{
    using point = bg::model::point
                  <double, 2, bg::cs::geographic<bg::degree>>;
                  //  <double, 2, bg::cs::spherical_equatorial<bg::degree>>;
                  //<double, 2, bg::cs::cartesian>;
    using linestring = bg::model::linestring<point>;

    linestring ls1;

    std::ifstream myfile ("Geolife_Trajectories_1.3/Data/010/Trajectory/20081224011945.plt");

    read_linestring(myfile, ls1);

    //compression or simplification
    linestring ls_simplified;
    bg::simplify(ls1, ls_simplified, 20);
    std::cout << "#points in  simplified ls1 = " << boost::size(ls_simplified)
              << std::endl;

    //densification
    using multipoint_type = bg::model::multi_point<point>;
    multipoint_type mp;
    bg::line_interpolate(ls1, 50.0, mp);
    std::cout << "#points interpolated on ls1 = " << boost::size(mp)
              << std::endl;

    // Declare a stream and an SVG mapper
    std::ofstream svg("my_map.svg");
    boost::geometry::svg_mapper<point> mapper(svg, 500, 500);

    // Add geometries such that all these geometries fit on the map
    mapper.add(ls1);
    mapper.add(mp);
    mapper.add(ls_simplified);

    // Draw the geometries on the SVG map, using a specific SVG style
    mapper.map(ls1, "opacity:1.0;fill:none;stroke:rgb(255,0,0);stroke-width:1");
    mapper.map(ls_simplified, "opacity:1.0;fill:none;stroke:rgb(0,0,255);stroke-width:1");
    mapper.map(mp, "opacity:1.0;fill:rgb(0,255,0);stroke:rgb(0,255,0);stroke-width:1", 2);

    return 0;
}
