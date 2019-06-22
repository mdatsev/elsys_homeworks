#include "point.hh"
#include <iostream>

Point::Point(double x, double y)
    : x_(x), y_(y) {}

void Point::print() const
{
}

double Point::get_x() const
{
    return x_;
}

double Point::get_y() const
{
    return y_;
}

void Point::set_x(double x)
{
    x_ = x;
}

void Point::set_y(double y)
{
    y_ = y;
}