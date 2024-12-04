#include "../include/Line.h"

Line::Line(double x1, double y1, double x2, double y2, const std::string& name) 
    : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _name(name) {
}

void Line::draw(cairo_t* cr) const {
    cairo_move_to(cr, _x1, _y1);
    cairo_line_to(cr, _x2, _y2);
    cairo_stroke(cr);
}

void Line::move(double dx, double dy) {
    _x1 += dx;
    _y1 += dy;
    _x2 += dx;
    _y2 += dy;
}

void Line::scale(double factor) {
    _x1 *= factor;
    _y1 *= factor;
    _x2 *= factor;
    _y2 *= factor;
}

std::string Line::get_name() const {
    return _name;
}
