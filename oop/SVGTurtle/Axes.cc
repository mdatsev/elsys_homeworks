#include "Axes.hh"

Axes::Axes(Turtle* turtle, const Color& color, double stroke_width)
    : turtle_(turtle), color_(color), stroke_width_(stroke_width)
{
    
}

void Axes::draw()
{
    auto w = turtle_->get_width(),
        h = turtle_->get_height();

    turtle_
    ->pencolor(color_)
    .pensize(stroke_width_)

    .penup()
    .moveto(Point(w / 2, 0))
    .pendown()
    .moveto(Point(w / 2, h))

    .penup()
    .moveto(Point(0, h / 2))
    .pendown()
    .moveto(Point(w, h / 2));
}