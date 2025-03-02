#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "Shape.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Composition {
private:
    std::vector<std::shared_ptr<Shape>> _shapes;
    std::string _name;

public:
    Composition(const std::string& name);
    void add_shape(std::shared_ptr<Shape> shape);
    void remove_shape(const std::string& name);
    void move_shape(const std::string& name, double dx, double dy);
    void move_comp(double dx, double dy);
    void scale(double factor);
    void draw(SDL_Renderer* renderer) const;
    void save_to_file(json& json_file) const;
    void load_from_file(json& comp_file);
    std::shared_ptr<Shape> get_shape_at(double x, double y) const;
    std::string get_name() const;
};

