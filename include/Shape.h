#pragma once
#include <cairo/cairo.h>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(cairo_t* cr) const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string get_name() const = 0;
};
