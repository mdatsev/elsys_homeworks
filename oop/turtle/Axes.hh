#include "turtle.hh"

class Axes
{
    Turtle* turtle_;
    Color color_;
    double stroke_width_;
public:
    Axes(Turtle* turtle, const Color& color, double stroke_width);
    void draw();
};