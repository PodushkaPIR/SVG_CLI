#include "../include/Line.h"
#include <iostream>

Line::Line(double x1, double y1, double x2, double y2, const std::string& name) 
    : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _name(name) {
}

void Line::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, static_cast<int>(_x1), static_cast<int>(_y1),
                       static_cast<int>(_x2), static_cast<int>(_y2));
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

void Line::save(json& shape_json) const {
    shape_json["type"] = "line";
    shape_json["name"] = get_name();
    shape_json["x1"] = _x1;
    shape_json["y1"] = _y1;
    shape_json["x2"] = _x2;
    shape_json["y2"] = _y2;
} 
std::shared_ptr<Shape> Line::load(const json& shape_json) {
    if (shape_json["type"] != "line") return nullptr;
    return std::make_shared<Line>(shape_json["x1"], shape_json["y1"], \
                                  shape_json["x2"], shape_json["y2"], shape_json["name"]);
}

bool Line::contains(double px, double py) const {
    double distance = std::abs((_y2 - _y1) * px - (_x2 - _x1) * py + _x2 * _y1 - _y2 * _x1) / 
                      std::sqrt((_y2 - _y1) * (_y2 - _y1) + (_x2 - _x1) * (_x2 - _x1));
    const double threshold = 5.0;
    return distance <= threshold;
}

std::string Line::get_name() const {
    return _name;
}
