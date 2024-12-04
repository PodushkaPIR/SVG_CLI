#pragma once
#include <string>
#include <SDL2/SDL.h>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(SDL_Renderer* renderer) const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual bool contains(double x, double y) const = 0;
    virtual std::string get_name() const = 0;
};
