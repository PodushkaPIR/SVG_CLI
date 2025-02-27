#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(SDL_Renderer* renderer) const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual bool contains(double px, double py) const = 0;
    virtual void save(json& shape_json) const = 0;
    static std::shared_ptr<Shape> load(const json& shape_json);
    virtual std::string get_name() const = 0;
};
