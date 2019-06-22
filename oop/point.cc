#include <iostream>
#include <stdio.h>

using namespace std;

class Point
{
  public:
    static const double default_cx = 0;
    static const double default_cy = 0;
    Point(const double x, const double y, const double cx = default_cx, const double cy = default_cy)
        : x_(x),
          y_(y), cx_(cx), cy_(cy) {}
    Point transform_in_default()
    {
        return transform_in(default_cx, default_cy);
    }
    Point transform_in(const double cx, const double cy)
    {
        return Point(x_ + cx_ - cx, y_ + cy_ - cy, cx, cy);
    }
    Point origin() const
    {
        return Point(cx_, cy_);
    }
    double get_x() const
    {
        return x_;
    }
    double get_y() const
    {
        return y_;
    }
    double get_cx() const
    {
        return cx_;
    }
    double get_cy() const
    {
        return cy_;
    }
    Point &set_x(const double x)
    {
        x_ = x;
        return *this;
    }
    Point &set_y(const double y)
    {
        y_ = y;
        return *this;
    }
    Point operator+(const Point &other) const
    {
        return Point(this->x_ + other.x_, this->y_ + other.y_);
    }
    Point operator-(const Point &other) const
    {
        return Point(this->x_ - other.x_, this->y_ - other.y_);
    }
    Point operator*(const double &number) const
    {
        return Point(this->x_ * number, this->y_ * number);
    }
    Point operator/(const double &number) const
    {
        return Point(this->x_ / number, this->y_ / number);
    }
    Point operator-() const
    {
        return Point(-this->x_, -this->y_);
    }
    Point &operator+=(const Point &other)
    {
        this->x_ += other.x_;
        this->y_ += other.y_;
        return *this;
    }
    Point &operator-=(const Point &other)
    {
        this->x_ -= other.x_;
        this->y_ -= other.y_;
        return *this;
    }
    Point &operator*=(const double &number)
    {
        this->x_ *= number;
        this->y_ *= number;
        return *this;
    }
    Point &operator/=(const double &number)
    {
        this->x_ /= number;
        this->y_ /= number;
        return *this;
    }

  private:
    double x_,
        y_,
        cx_,
        cy_;
};

Point operator*(const double &number, const Point &point)
{
    return Point(point.get_x() * number, point.get_y() * number);
}
ostream &operator<<(ostream &out, const Point &p)
{
    out << "Point(" << p.get_x() << "," << p.get_y() << ")";
    return out;
}
main()
{
    Point p1(1.2, 2);
    Point p2(2, 3);
    p1 -= p2;
    cout << p1.origin();
}