#include "../include/Composition.h"
#include <algorithm>

Composition::Composition(const std::string& name) : _name(name) {}

void Composition::add_shape(std::shared_ptr<Shape> shape) {
    _shapes.push_back(shape);
}

void Composition::remove_shape(const std::string& name) {
    _shapes.erase(std::remove_if(_shapes.begin(), _shapes.end(),
                                [&name](const std::shared_ptr<Shape>& shape) {
                                return shape->get_name() == name;
                                }), _shapes.end());
}


void Composition::move_shape(const std::string& shape_name, int dx, int dy) {
    for (auto& shape : _shapes) {
        if (shape->get_name() == shape_name) {
            shape->move(dx, dy);
            break;
        }
    }
}

void Composition::scale(double factor) {
    for (auto& shape : _shapes) {
        shape->scale(factor);
    }
}

void Composition::draw(SDL_Renderer* renderer, int scale_x, int scale_y) const {
    for (const auto& shape : _shapes) {
        shape->draw(renderer, scale_x, scale_y);
    }
}

void Composition::save_to_file(const std::string& filename) const {
    // Здесь будет код для сохранения композиции в файл
}

void Composition::load_from_file(const std::string& filename) {
    // Здесь будет код для загрузки композиции из файла
}

std::string Composition::get_name() const {
    return _name;
}

