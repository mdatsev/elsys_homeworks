#include <map>
#include "turtle.hh"

using turtle_map_type = std::map<std::string, Turtle*(*)(double, double, std::ostream&)>;

extern turtle_map_type turtle_map;

Turtle* getTurtle(const char* format, double width, double height, std::ostream& out);