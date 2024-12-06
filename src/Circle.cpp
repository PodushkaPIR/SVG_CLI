#include "../include/Circle.h"

Circle::Circle(double x, double y, double radius, const std::string& name)
    : _x(x), _y(y), _radius(radius), _name(name) {}

void Circle::draw(SDL_Renderer* renderer) const {
    for (double angle = 0; angle < 2 * M_PI; angle += 0.01) {
        double x1 = _x + _radius * std::cos(angle);
        double y1 = _y + _radius * std::sin(angle);
        double x2 = _x + _radius * std::cos(angle + 0.01);
        double y2 = _y + _radius * std::sin(angle + 0.01);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderDrawLine(renderer, static_cast<int>(x1), static_cast<int>(y1),
                           static_cast<int>(x2), static_cast<int>(y2));
    }
}

void Circle::scale(double factor) {
    _radius *= factor;
}

void Circle::move(double dx, double dy) {
    _x += dx;
    _y += dy;
}

void Circle::save(std::ofstream& out_file) const {
    out_file << "Circle" << " " << _x << " " << _y << " " << _radius << " " << _name << "\n";
}

std::shared_ptr<Shape> Circle::load(std::ifstream& input_file) {
    std::string type;
    input_file >> type;
    if (type != "Circle") {
        return nullptr;
    }
    double x, y, radius;
    std::string name;
    input_file >> x >> y >> radius >> name;
    return std::make_shared<Circle>(x, y, radius, name);
}

std::string Circle::get_name() const {
    return _name;
}

bool Circle::contains(double x, double y) const {
    double distance = std::sqrt((_x - x) * (_x - x) + (_y - y) * (_y - y));
    return distance <= _radius;
}
