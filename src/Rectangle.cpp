#include "../include/Rectangle.h"

Rectangle::Rectangle(double x, double y, double width, double height, const std::string& name)
    : _x(x), _y(y), _width(width), _height(height), _name(name) {}

void Rectangle::draw(SDL_Renderer* renderer) const {
    for (double angle = 0; angle < 2 * M_PI; angle += 0.01) {
        SDL_Rect rect = {static_cast<int>(_x), static_cast<int>(_y),
                         static_cast<int>(_width), static_cast<int>(_height)};
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Rectangle::scale(double factor) {
    _width *= factor;
    _height *= factor;
}

void Rectangle::move(double dx, double dy) {
    _x += dx;
    _y += dy;
}

std::string Rectangle::get_name() const {
    return _name;
}

bool Rectangle::contains(double x, double y) const {
    return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height);
}

