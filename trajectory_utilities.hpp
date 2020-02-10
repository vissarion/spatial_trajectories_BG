#ifndef TRAJECTORY_UTILITIES_HPP
#define TRAJECTORY_UTILITIES_HPP

namespace bg = boost::geometry;

template <typename Linestring>
void read_linestring(std::ifstream & myfile,
                     Linestring & ls)
{
    if (myfile.is_open())
    {
        size_t line_count = 0;
        typedef typename bg::point_type<Linestring>::type point;
        point p;
        std::string line;
        while ( std::getline(myfile, line))
        {
            if (line_count++ < 6) continue;
            std::string delimiter = ",";
            std::string token1, token2;
            size_t pos = line.find(delimiter);
            token1 = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            token2 = line.substr(0, pos);
            p = point(std::stod(token2), std::stod(token1));
            bg::append(ls, p);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

#endif // TRAJECTORY_UTILITIES_HPP
