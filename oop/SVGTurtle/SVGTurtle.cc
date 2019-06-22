#include "SVGTurtle.hh"

std::string attr(const std::string& name, const std::string& value)
{
	return " " + name + "=" + '"' + value + '"';
}

std::string attr(const std::string& name, double value)
{
	return attr(name, std::to_string(value));
}

std::string prop(const std::string& name, const std::string& value)
{
	return name + ":" + value + ";";
}

std::string prop(const std::string& name, double value)
{
	return prop(name, std::to_string(value));
}

std::string css_color(const Color& color)
{
	return "rgb(" +
		std::to_string((int)(color.red() * 255)) + "," +
		std::to_string((int)(color.green() * 255)) + "," +
		std::to_string((int)(color.blue() * 255)) +
		")";
}

std::string prop(const std::string& name, const Color& value)
{
	return prop(name, css_color(value));
}

std::string line_tag(const Point& p1, const Point& p2, const Color& color, double stroke_width)
{
	return
		"<line" +
		attr("x1", p1.get_x()) +
		attr("y1", p1.get_y()) +
		attr("x2", p2.get_x()) +
		attr("y2", p2.get_y()) +
		attr("style",
			prop("stroke", color) +
			prop("stroke-width", stroke_width)) +
		"/>" + "\n";
}

SVGTurtle::SVGTurtle(double width, double height,
	std::ostream& out)
	: Turtle(width, height), out_(out)
{
}

SVGTurtle::~SVGTurtle()
{
	out_ << "</svg>\n</body>\n</html>";
}

//virtual void setup();
Turtle& SVGTurtle::setup()
{
	Turtle::setup();
	out_ << "<html>\n<body>\n<h1>SVG Turtle Graphics</h1>\n<svg" +
		attr("width", get_width()) +
		attr("height", get_height()) +
		">\n";
	return *this;
}

Turtle& SVGTurtle::moveto(const Point& p)
{
	if (is_pendown())
		out_ << line_tag(get_pos(), p, get_color(), get_pensize());
	set_pos(p);
	return *this;
}