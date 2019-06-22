#include "turtle.hh"
#include "SVGturtle.hh"
#include <cmath>
#include "Axes.hh"
#include "turtle_map.hh"

class Star
{
    Turtle* turtle_;
    Color color_;
    double stroke_width_;
	double side_len_;
public:
    Star(Turtle* turtle, double side_length, const Color& color, double stroke_width)
		: turtle_(turtle), side_len_(side_length), color_(color), stroke_width_(stroke_width)
	{

	}
    void draw()
	{
		turtle_
		->pencolor(color_)
    	.pensize(stroke_width_)
		.penup()
		.set_pos(Point(turtle_->get_width() / 2, turtle_->get_height() / 2)) //set to center and then walk back 
		.backward(side_len_) //walk back so the star is centered
		.right(60)
		.backward(side_len_)
		.set_heading(0)
		.pendown();
		for (int i = 0; i < 6; i++)
		{
			turtle_
			->forward(side_len_)
			.left(60)
			.forward(side_len_)
			.right(120);
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
		Star star(turtle, 200, Color(0, 1, 0), 7);
		axes.draw();
		star.draw();
        delete turtle;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
    }
}