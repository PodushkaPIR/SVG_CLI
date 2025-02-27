#include <SDL2/SDL.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../include/Terminal.h"
#include "../include/Utility.h"
#include "../include/CompositionManager.h"


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    CompositionManager manager; 

    manager.create_composition("Default");
    manager.set_current_composition("Default");
    
    std::thread command_thread(handle_commands, std::ref(manager));

    print_help();

    bool quit = false;
    while (!quit) {
        handle_events(window, renderer, manager);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer);

        manager.draw_all_compositions(renderer);

        SDL_RenderPresent(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    command_thread.join();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

