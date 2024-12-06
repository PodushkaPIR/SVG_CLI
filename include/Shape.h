#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <SDL2/SDL.h>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(SDL_Renderer* renderer) const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual bool contains(double x, double y) const = 0;
    virtual void save(std::ofstream& out_file) const = 0;
    virtual std::string get_name() const = 0;
    static std::shared_ptr<Shape> load(std::ifstream& input_file);
};
