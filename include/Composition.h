#pragma once
#include <vector>
#include <memory>
#include "Shape.h"

class Composition {
private:
    std::vector<std::shared_ptr<Shape>> _shapes;
    std::string _name;

public:
    Composition(const std::string& name);
    void add_shape(std::shared_ptr<Shape> shape);
    void remove_shape(const std::string& name);
    void move_shape(const std::string& name, int dx, int dy);
    void scale(double factor);
    void draw(SDL_Renderer* renderer) const;
    void save_to_file(const std::string& filename) const;
    void load_from_file(const std::string& filename);
    std::shared_ptr<Shape> get_shape_at(double x, double y) const;
    std::string get_name() const;
};

