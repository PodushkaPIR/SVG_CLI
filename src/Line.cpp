#include "../include/Line.h"

Line::Line(double x1, double y1, double x2, double y2, const std::string& name) 
    : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _name(name) {
}

void Line::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, _x1, _y1, _x2, _y2);
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

bool Line::contains(double x, double y) const {
    double distance = std::abs((_y2 - _y1) * x - (_x2 - _x1) * y + _x2 * _y1 - _y2 * _x1) / 
                      std::sqrt((_y2 - _y1) * (_y2 - _y1) + (_x2 - _x1) * (_x2 - _x1));
    const double threshold = 5.0;
    return distance <= threshold;
}

std::string Line::get_name() const {
    return _name;
}
