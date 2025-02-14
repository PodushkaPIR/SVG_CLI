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

void Rectangle::save(std::ofstream& out_file) const {
    out_file << "Rectangle\n" << _x << " " << _y << " " << _width << " " << _height << " " << _name << "\n";
}

std::shared_ptr<Shape> Rectangle::load(std::ifstream& input_file) {
    double x, y, width, height;
    std::string name;
    input_file >> x >> y >> width >> height >> name;
    return std::make_shared<Rectangle>(x, y, width, height, name);
}

std::string Rectangle::get_name() const {
    return _name;
}

bool Rectangle::contains(double px, double py) const {
    return (px >= _x && px <= _x + _width && py >= _y && py <= _y + _height);
}

