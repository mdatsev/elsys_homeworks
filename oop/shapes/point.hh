#pragma once

#include "shape.hh"

class Point
{
    double x_, y_;

  public:
    Point(double x, double y);
    void print() const;
    double get_x() const;
    double get_y() const;
    void set_x(double);
    void set_y(double);
};