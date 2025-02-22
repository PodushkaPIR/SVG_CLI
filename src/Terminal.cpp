#include "../include/Terminal.h"
#include <iostream>
#include <vector>
#include <linenoise.h>
#include <sstream>

const std::vector<std::string> commands = {
    "add", "scale", "move", "remove", "save", "load", "exit", "help"
};

void print_help() {
    std::cout << R"(
----------------------------------------------------------
Available commands:
----------------------------------------------------------
add <type> <name> [params] - Add new shape
    Types:
      line <name> <x1> <y1> <x2> <y2>
      circle <name> <x> <y> <radius>
      rectangle <name> <x> <y> <width> <height>
      parallelogram <name> <x> <y> <skew> <width> <height>

scale <factor> - Scale all shapes
move <name> <dx> <dy> - Move a shape
remove <name> - Remove a shape
save <filename> - Save the composition to a file
load <filename> - Load the composition from the file
exit - Exit the program
help - Show this help message
----------------------------------------------------------
    )";
}

void print_shape(std::shared_ptr<Shape> shape) {
    std::cout << '\n';
    std::cout << "Clicked on the shape: " << shape->get_name() << "\n";
    std::cout << R"(
----------------------------------------------------------
Available commands for this shape:
----------------------------------------------------------
move <name> <dx> <dy> - Move a shape
remove <name> - Remove a shape
----------------------------------------------------------
    )";
}

void handle_events(SDL_Window* window, SDL_Renderer* renderer, Composition& comp) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            std::exit(0);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::shared_ptr<Shape> shape = comp.get_shape_at(static_cast<double>(x), static_cast<double>(y));
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

void handle_commands(Composition& comp) {

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
                std::string type, name;
                double x1, y1, x2, y2, radius, width, height, skew;
                iss >> type >> name;
                if (type == "line") {
                    iss >> x1 >> y1 >> x2 >> y2;
                    comp.add_shape(std::make_shared<Line>(x1, y1, x2, y2, name));
                }
                else if (type == "circle") {
                    iss >> x1 >> y1 >> radius;
                    comp.add_shape(std::make_shared<Circle>(x1, y1, radius, name));
                }
                else if (type == "rectangle") {
                    iss >> x1 >> y1 >> width >> height;
                    comp.add_shape(std::make_shared<Rectangle>(x1, y1, width, height, name));
                }
                else if (type == "parallelogram") {
                    iss >> x1 >> y1 >> skew >> width >> height;
                    comp.add_shape(std::make_shared<Parallelogram>(x1, y1, skew, width, height, name));
                }
            }
            else if (command == "scale") {
                double factor;
                iss >> factor;
                comp.scale(factor);
            }
            else if (command == "move") {
                std::string name;
                double dx, dy;
                iss >> name >> dx >> dy;
                comp.move_shape(name, dx, dy);
            }
            else if (command == "remove") {
                std::string name;
                iss >> name;
                comp.remove_shape(name);
            }
            else if (command == "save") {
                std::string filename;
                iss >> filename;
                comp.save_to_file(filename);
            }
            else if (command == "load") {
                std::string filename;
                iss >> filename;
                comp.load_from_file(filename);
            }
            else if (command == "exit") {
                linenoiseHistoryAdd(line);
                linenoiseHistorySave("history.txt");
                std::exit(0);
            }
            else if (command == "help") {
                print_help();
            }

            linenoiseHistoryAdd(line);
        }

        delete line;
    }
}
