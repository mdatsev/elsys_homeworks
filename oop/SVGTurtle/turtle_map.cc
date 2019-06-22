#include "turtle_map.hh"

#include "turtle.hh"
#include "SVGTurtle.hh"

template <typename T>
Turtle* createInstance(double width, double height, std::ostream& out){
    return new T(width, height, out);
}

turtle_map_type turtle_map = {
    {"ps", &createInstance<PSTurtle>},    
    {"eps", &createInstance<PSTurtle>},
    {"svg", &createInstance<SVGTurtle>}
};

Turtle* getTurtle(const char* format, double width, double height, std::ostream& out){
    try{
        return turtle_map.at(format)(width, height, out);
    }
    catch(std::out_of_range& e){
        throw std::invalid_argument("Format not found or not supported.");
    }
}