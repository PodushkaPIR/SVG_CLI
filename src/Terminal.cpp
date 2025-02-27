#include "../include/Terminal.h"
#include "../include/CompositionManager.h"
#include <iostream>
#include <vector>
#include <linenoise.h>
#include <sstream>

const std::vector<std::string> commands = {
    "add", "scale", "move", "remove", "save", "load", "create", "switch", "remove_comp", "exit", "help"
};

void print_help() {
    std::cout << R"(
---------------------------------------------------------------
Available commands:
---------------------------------------------------------------
add <composition_name> <type> <name> [params] - Add new shape
    Types:
      line <name> <x1> <y1> <x2> <y2>
      circle <name> <x> <y> <radius>
      rectangle <name> <x> <y> <width> <height>
      parallelogram <name> <x> <y> <skew> <width> <height>

scale <factor> - Scale all shapes in the current composition
move <name> <dx> <dy> - Move a shape in the current composition
remove <name> - Remove a shape from the current composition
save <filename> - Save the current composition to a file
load <filename> - Load a composition from a file
create <name> - Create a new composition
switch <name> - Switch to a composition
remove_comp <name> - Remove a composition
exit - Exit the program
help - Show this help message
---------------------------------------------------------------
    )";
}

void print_shape(std::shared_ptr<Shape> shape) {
    std::cout << '\n';
    std::cout << "Clicked on the shape: " << shape->get_name() << "\n";
    std::cout << R"(
---------------------------------------------------------------
Available commands for this shape:
---------------------------------------------------------------
move <name> <dx> <dy> - Move a shape
remove <name> - Remove a shape
---------------------------------------------------------------
    )";
}

void handle_events(SDL_Window* window, SDL_Renderer* renderer, CompositionManager& manager) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            std::exit(0);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            auto current_composition = manager.get_current_composition();
            if (current_composition) { 
                std::shared_ptr<Shape> shape = current_composition->get_shape_at(static_cast<double>(x), static_cast<double>(y));
                if (shape != nullptr) {
                    std::cout << "\r";
                    for (size_t i = 0; i < 9; ++i) {
                        std::cout << " ";
                    }
                    std::cout << "\r";

                    print_shape(shape);

                    std::cout << "\rcommand: ";
                    std::cout.flush();
                }
            } 

            else {
                std::cout << "No current composition selected!" << std::endl;
            }
        }
    }
}

void completion(const char* buf, linenoiseCompletions* lc) {
    std::string input(buf);

    for (const auto& cmd : commands) {
        if (cmd.find(input) == 0) {
            linenoiseAddCompletion(lc, cmd.c_str());
        }
    }
}

void handle_commands(CompositionManager& manager) {

    linenoiseSetCompletionCallback(completion);
    linenoiseHistoryLoad("history.txt");

    while (true) {
        char* line = linenoise("command: ");
        if (line == nullptr) {
            break;
        }

        if (line[0] != '\0') {
            std::istringstream iss(line);
            std::string command;
            iss >> command;

            if (command == "add") {
                std::string comp_name, type, name;
                double x1, y1, x2, y2, radius, width, height, skew;
                iss >> comp_name >> type >> name;

                auto composition = manager.get_composition(comp_name);

                if (type == "line") {
                    iss >> x1 >> y1 >> x2 >> y2;
                    composition->add_shape(std::make_shared<Line>(x1, y1, x2, y2, name));
                }
                else if (type == "circle") {
                    iss >> x1 >> y1 >> radius;
                    composition->add_shape(std::make_shared<Circle>(x1, y1, radius, name));
                }
                else if (type == "rectangle") {
                    iss >> x1 >> y1 >> width >> height;
                    composition->add_shape(std::make_shared<Rectangle>(x1, y1, width, height, name));
                }
                else if (type == "parallelogram") {
                    iss >> x1 >> y1 >> skew >> width >> height;
                    composition->add_shape(std::make_shared<Parallelogram>(x1, y1, skew, width, height, name));
                }
            }

            else if (command == "scale") {
                double factor;
                iss >> factor;
                manager.get_current_composition()->scale(factor);
            }
            else if (command == "move") {
                std::string name;
                double dx, dy;
                iss >> name >> dx >> dy;
                manager.get_current_composition()->move_shape(name, dx, dy);
            }
            else if (command == "remove") {
                std::string name;
                iss >> name;
                manager.get_current_composition()->remove_shape(name);
            }
            else if (command == "save") {
                std::string filename;
                iss >> filename;
                manager.save_all_compositions(filename);
            }
            else if (command == "load") {
                std::string filename;
                iss >> filename;
                manager.load_all_compositions(filename);
            }
            else if (command == "create") {
                std::string name;
                iss >> name;
                manager.create_composition(name);
            }
            else if (command == "switch") {
                std::string name;
                iss >> name;
                manager.set_current_composition(name);
            }
            else if (command == "remove_comp") {
                std::string name;
                iss >> name;
                manager.remove_composition(name);
            }
            else if (command == "exit") {
                linenoiseHistoryAdd(line);
                linenoiseHistorySave("history.txt");
                std::exit(0);
            }
            else if (command == "help") {
                print_help();
            }
            else {
                std::cout << "Unknown command. Type 'help' for a list of commands.\n";
            }

            linenoiseHistoryAdd(line);
        }

        delete line;
    }
}
