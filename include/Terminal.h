#include <iostream>
#include "Shape.h"
#include "Composition.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"

void print_help();
void print_shape(std::shared_ptr<Shape> shape);
void handle_events(SDL_Window* window, SDL_Renderer* renderer, Composition& comp);
void handle_commands(Composition& comp);
