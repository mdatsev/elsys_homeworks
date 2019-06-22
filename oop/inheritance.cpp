#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Point
{
    double x_, y_;

  public:
    Point(double x = 0.0, double y = 0.0)
        : x_(x), y_(y)
    {
    }
    double get_x() const
    {
        return x_;
    }
    double get_y() const
    {
        return y_;
    }
    friend ostream &operator<<(ostream &stream, const Point &p)
    {
        stream << "P(" << p.x_ << ", " << p.y_ << ")";
    }
};

class Shape
{
  public:
    virtual void draw() const = 0;
};

class Circle : public Shape
{
    Point center_;
    double radius_;

  public:
    Circle(Point center, double radius)
        : center_(center), radius_(radius)
    {
    }
    void draw() const
    {
        cout << "C(" << center_ << ";" << radius_ << ")" << endl;
    }
};

class Rectangle : public Shape
{
    Point ul_, br_;

  public:
    Rectangle(const Point &p1, const Point &p2)
        : ul_(p1), br_(p2)
    {
    }
    void draw() const
    {
        cout << "R(" << ul_ << ";" << br_ << ")" << endl;
    }
};

int main()
{
    vector<Shape *> shapes;
    Circle c1 = Circle(Point(-3, 0), 3.0);
    Circle c2 = Circle(Point(3, 0), 3.0);
    shapes.push_back(&c1);
    shapes.push_back(&c2);
    Rectangle r1 = Rectangle(Point(1, 2), Point(2, 3));
    Rectangle r2 = Rectangle(Point(-1, -2), Point(-2, -3));
    shapes.push_back(&r1);
    shapes.push_back(&r1);
    for (int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->draw();
    }
}
