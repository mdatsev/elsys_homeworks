#include "turtle.hh"
#include "SVGturtle.hh"
#include <cmath>
#include "turtle_map.hh"
#include "memory"

class SierpinskiCurve
{
    Turtle *turtle_;
    Color color_;
    double stroke_width_;
    double big_side_len_;
    double small_side_len_;
    int order_;

  public:
    SierpinskiCurve(Turtle *turtle, double max_square_length, int order, const Color &color, double stroke_width)
        : turtle_(turtle), order_(order), big_side_len_(max_square_length / std::pow(2, order + 1)), small_side_len_(big_side_len_ / std::sqrt(2)), color_(color), stroke_width_(stroke_width)
    {
    }
    void draw()
    {
        turtle_
            ->pencolor(color_)
            .pensize(stroke_width_)
            .set_pos(Point(1. / 2 * big_side_len_, big_side_len_))
            .pendown()
            .set_heading(-135);
        drawTurn();
        draw(order_, false);
    }

    void drawJoin()
    {
        turtle_
            ->right(45)
            .forward(big_side_len_)
            .right(45);
    }

    void drawSide()
    {
        turtle_->forward(small_side_len_);
        drawJoin();
        turtle_->forward(small_side_len_);
    }

    void drawHalf()
    {
        drawSide();
        drawTurn();
        drawSide();
    }

    void drawTurn()
    {
        turtle_
            ->left(90)
            .forward(small_side_len_)
            .left(90);
    }

    void draw(int ord, bool half)
    {
        if (ord == 1)
        {
            drawHalf();
            if (half)
                return;
            drawTurn();
            drawHalf();
        }
        else
        {
            draw(ord - 1, true);
            drawJoin();
            draw(ord - 1, false);
            drawJoin();
            draw(ord - 1, half);
            if (half)
                return;
            drawJoin();
            draw(ord - 1, false);
            drawJoin();
            draw(ord - 1, true);
        }
    }
};

int main(int argc, char *argv[])
{
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <format> <order>" << std::endl;
        return -1;
    }
    const char* format = argv[1];
    int order = atoi(argv[2]);
    constexpr int canvas_size = 2048;
    try
    {
        Turtle* turtle = getTurtle(format, canvas_size, canvas_size, std::cout);
        turtle->setup();
        SierpinskiCurve sc(turtle, canvas_size, order, Color(0, 0, 0), 10 / order);
        sc.draw();
        delete turtle;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
    }
}