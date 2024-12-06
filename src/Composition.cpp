#include "../include/Composition.h"
#include <algorithm>
#include <iostream>
#include <fstream>

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

void Composition::draw(SDL_Renderer* renderer) const {
    for (const auto& shape : _shapes) {
        shape->draw(renderer);
    }
}

std::shared_ptr<Shape> Composition::get_shape_at(double x, double y) const {
    for (const auto& shape : _shapes) {
        if (shape->contains(x, y)) {
            return shape;
        }
    }
    return nullptr;
}

void Composition::save_to_file(const std::string& filename) const {
    std::ofstream out_file(filename);
    if (!out_file) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    out_file << _shapes.size() << "\n";
    for (const auto& shape : _shapes) {
        shape->save(out_file);
    }
}

void Composition::load_from_file(const std::string& filename) {
    std::ifstream input_file(filename);
    if (!input_file) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    size_t count;
    input_file >> count;
    _shapes.clear();
    for (size_t i = 0; i < count; ++i) {
        std::shared_ptr<Shape> shape = Shape::load(input_file);
        // std::cout << shape->get_name() << "\n";
        if (shape) {
            add_shape(shape);
        }
    }
}

std::string Composition::get_name() const {
    return _name;
}

