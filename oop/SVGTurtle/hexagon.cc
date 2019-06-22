#include "turtle.hh"
#include "SVGturtle.hh"
#include <cmath>
#include "Axes.hh"
#include "turtle_map.hh"

class Hexagon
{
    Turtle* turtle_;
    Color color_;
    double stroke_width_;
	double side_len_;
public:
    Hexagon(Turtle* turtle, double side_length, const Color& color, double stroke_width)
		: turtle_(turtle), side_len_(side_length), color_(color), stroke_width_(stroke_width)
	{

	}
    void draw()
	{
		turtle_
		->pencolor(color_)
    	.pensize(stroke_width_)

		.set_pos(Point(turtle_->get_width() / 2 - side_len_ / 2, //half the width minus half the radius to the vertex = side len
			turtle_->get_height() / 2 + std::sqrt(3) / 2 * side_len_)) //half the height minus radius to the side = √3 / 2 * side_len 
		.pendown();
		for (int i = 0; i < 6; i++)
		{
			turtle_
			->forward(side_len_)
			.right(60);
		}
	}
};

int main(int argc, const char* argv[])
{
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " <format>" << std::endl;
        return -1;
    }
    try
    {
        Turtle* turtle = getTurtle(argv[1], 1000, 1000, std::cout);
        turtle->setup();
		Axes axes(turtle, Color(0, 0, 0), 1);
		Hexagon hexagon(turtle, 400, Color(1, 0, 0), 7);
		axes.draw();
		hexagon.draw();
        delete turtle;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
    }
}