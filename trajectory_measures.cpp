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
                  //<double, 2, bg::cs::spherical_equatorial<bg::degree>>;
                  //<double, 2, bg::cs::cartesian>;
    using linestring = bg::model::linestring<point>;

    linestring ls1, ls2;
    std::ifstream myfile1 ("Geolife_Trajectories_1.3/Data/000/Trajectory/20090516091038.plt");
    std::ifstream myfile2 ("Geolife_Trajectories_1.3/Data/010/Trajectory/20081224011945.plt");

    read_linestring(myfile1, ls1);
    read_linestring(myfile2, ls2);

    //size
    std::cout << "#points in ls1 = " << boost::size(ls1) << std::endl;
    std::cout << "#points in ls2 = " << boost::size(ls2) << std::endl;

    //length
    std::cout << "ls1 length (m) = " << bg::length(ls1) << std::endl;
    std::cout << "ls2 length (m) = " << bg::length(ls2) << std::endl;

    //distance
    std::cout << "distance (m) = " << bg::distance(ls1, ls2) << std::endl;

    //closest points
    bg::model::segment<point> sout;
    bg::closest_points(ls1, ls2, sout);
    std::cout << bg::wkt(sout) << std::endl;

    //similarity
    std::cout << "Hausdorff = " <<  bg::discrete_hausdorff_distance(ls1, ls2) << std::endl;

    //Frechet
    std::cout << "Frechet = " << bg::discrete_frechet_distance(ls1, ls2) << std::endl;

    return 0;
}
