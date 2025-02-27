#include "../include/Rectangle.h"

Rectangle::Rectangle(double x, double y, double width, double height, const std::string& name)
    : _x(x), _y(y), _width(width), _height(height), _name(name) {}

void Rectangle::draw(SDL_Renderer* renderer) const {
    SDL_Rect rect = {static_cast<int>(_x), static_cast<int>(_y),
        static_cast<int>(_width), static_cast<int>(_height)};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &rect);
}

void Rectangle::scale(double factor) {
    _width *= factor;
    _height *= factor;
}

void Rectangle::move(double dx, double dy) {
    _x += dx;
    _y += dy;
}

void Rectangle::save(json& shape_json) const {
    shape_json["type"] = "rectangle";
    shape_json["name"] = get_name();
    shape_json["x"] = _x;
    shape_json["y"] = _y;
    shape_json["width"] = _width;
    shape_json["height"] = _height;
} 

std::shared_ptr<Shape> Rectangle::load(const json& shape_json) {
    if (shape_json["type"] != "rectangle") return nullptr;
    return std::make_shared<Rectangle>(shape_json["x"], shape_json["y"], \
                                       shape_json["width"], shape_json["height"], shape_json["name"]);
}

std::string Rectangle::get_name() const {
    return _name;
}

bool Rectangle::contains(double px, double py) const {
    return (px >= _x && px <= _x + _width && py >= _y && py <= _y + _height);
}

