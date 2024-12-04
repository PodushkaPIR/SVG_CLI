#include "../include/Line.h"

Line::Line(int x1, int y1, int x2, int y2, const std::string& name) 
    : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _name(name) {
}

void Line::draw(SDL_Renderer* renderer, int scale_x, int scale_y) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, _x1 * scale_x, _y1 * scale_y, _x2 * scale_x, _y2 * scale_y);
}

void Line::move(int dx, int dy) {
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
