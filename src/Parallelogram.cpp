#include "../include/Parallelogram.h"

Parallelogram::Parallelogram(double x, double y, double skew, double width, double height, const std::string& name)
    : _x(x), _y(y), _skew(skew), _width(width), _height(height), _name(name) {}

void Parallelogram::draw(SDL_Renderer* renderer) const {
    SDL_Point points[5];
    points[0] = {static_cast<int>(_x), static_cast<int>(_y)};
    points[1] = {static_cast<int>(_x + _width), static_cast<int>(_y)};
    points[2] = {static_cast<int>(_x + _width + _skew), static_cast<int>(_y + _height)};
    points[3] = {static_cast<int>(_x + _skew), static_cast<int>(_y + _height)};
    points[4] = points[0];

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLines(renderer, points, 5);
}


void Parallelogram::scale(double factor) {
    _width *= factor;
    _height *= factor;
}

void Parallelogram::move(double dx, double dy) {
    _x += dx;
    _y += dy;
}

void Parallelogram::save(std::ofstream& out_file) const {
    out_file << "Parallelogram\n" << _x << " " << _y << " " << _skew << " " << _width << " " << _height << " " << _name << "\n";
}

std::shared_ptr<Shape> Parallelogram::load(std::ifstream& input_file) {
    double x, y, skew, width, height;
    std::string name;
    input_file >> x >> y >> skew >> width >> height >> name;
    return std::make_shared<Parallelogram>(x, y, skew, width, height, name);
}

std::string Parallelogram::get_name() const {
    return _name;
}

bool Parallelogram::contains(double px, double py) const {
    double tx = px - _x;
    double ty = py - _y;

    double u = ty / _height;
    double v = (tx - _skew * ty / _height) / _width;

    return (u >= 0 && u <= 1 && v >= 0 && v <= 1);
}
