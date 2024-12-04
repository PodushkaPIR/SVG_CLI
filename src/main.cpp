#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/Composition.h"
#include "../include/Line.h"
#include "../include/Utility.h"

void handle_events(SDL_Window* window, SDL_Renderer* renderer, Composition& comp) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            std::exit(0);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            // std::cout << "Coords (x,y): " << x << " " << y << "\n";
            std::shared_ptr<Shape> shape = comp.get_shape_at(static_cast<double>(x), static_cast<double>(y));
            if (shape != nullptr) {
                std::cout << "Clicked on shape: " << shape->get_name() << std::endl;
            }
        }
    }
}

void handle_commands(Composition& comp) {
    std::string command;
    while (true) {
        std::cout << "Type one of the commands (add, scale, move, remove, exit)\n";
        std::cin >> command;
        if (command == "add") {
            std::cout << "Type using this template: 'name, x1, y1, x2, y2'\n";
            std::string name;
            int x1, y1, x2, y2;
            std::cin >> name >> x1 >> y1 >> x2 >> y2;
            comp.add_shape(std::make_shared<Line>(x1, y1, x2, y2, name));
        } else if (command == "scale") {
            std::cout << "Type the factor:\n";
            double factor;
            std::cin >> factor;
            comp.scale(factor);
        } else if (command == "move") {
            std::cout << "Type using this template: 'name, dx, dy'\n";
            std::string name;
            int dx, dy;
            std::cin >> name >> dx >> dy;
            comp.move_shape(name, dx, dy);
        } else if (command == "remove") {
            std::cout << "Type the name:\n";
            std::string name;
            std::cin >> name;
            comp.remove_shape(name);
        } else if (command == "exit") {
            std::exit(0);
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Composition comp("Test Composition");
    comp.add_shape(std::make_shared<Line>(10, 10, 600, 600, "Line1"));

    std::thread command_thread(handle_commands, std::ref(comp));

    bool quit = false;
    while (!quit) {
        handle_events(window, renderer, comp);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        comp.draw(renderer);

        SDL_RenderPresent(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    command_thread.join();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

