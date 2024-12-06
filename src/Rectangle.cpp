#include "../include/Rectangle.h"

Rectangle::Rectangle(double x, double y, double width, double height, const std::string& name)
    : _x(x), _y(y), _width(width), _height(height), _name(name) {}

void Rectangle::draw(SDL_Renderer* renderer) const {
    for (double angle = 0; angle < 2 * M_PI; angle += 0.01) {
        SDL_Rect rect = {static_cast<int>(_x), static_cast<int>(_y),
                         static_cast<int>(_width), static_cast<int>(_height)};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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

void Rectangle::save(std::ofstream& out_file) const {
    out_file << "Rectangle" << " " << _x << " " << _y << " " << _width << " " << _height << " " << _name << "\n";
}

std::shared_ptr<Shape> Rectangle::load(std::ifstream& input_file) {
    std::string type;
    input_file >> type;
    if (type != "Rectangle") {
        return nullptr;
    }
    double x, y, width, height;
    std::string name;
    input_file >> x >> y >> width >> height >> name;
    return std::make_shared<Rectangle>(x, y, width, height, name);
}

std::string Rectangle::get_name() const {
    return _name;
}

bool Rectangle::contains(double x, double y) const {
    return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height);
}

