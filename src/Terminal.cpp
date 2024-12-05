#include "../include/Terminal.h"
#include <linenoise.h>
#include <sstream>


void print_help() {
    std::cout << "Available commands:" << "\n";
    std::cout << "  add <type> <name> [params] - Add a new shape" << "\n";
    std::cout << "    Types:" << "\n";
    std::cout << "      line <name> <x1> <y1> <x2> <y2>" << "\n";
    std::cout << "      circle <name> <x> <y> <radius>" << "\n";
    std::cout << "      rectangle <name> <x> <y> <width> <height>" << "\n";
    std::cout << "  scale <factor> - Scale all shapes" << "\n";
    std::cout << "  move <name> <dx> <dy> - Move a shape" << "\n";
    std::cout << "  remove <name> - Remove a shape" << "\n";
    std::cout << "  exit - Exit the program" << "\n";
    std::cout << "  help - Show this help message" << "\n";
}

void print_shape(std::shared_ptr<Shape> shape) {
    std::cout << "Clicked on shape: " << shape->get_name() << "\n";
    std::cout << "Available commands for this shape:" << "\n";
    std::cout << "  move <name> <dx> <dy> - Move the shape" << "\n";
    std::cout << "  remove <name> - Remove the shape" << "\n";
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
                print_shape(shape);
            }
        }
    }
}

void handle_commands(Composition& comp) {
    std::string command;

    linenoiseSetCompletionCallback([](const char* buf, linenoiseCompletions* lc) {
        if (buf[0] == 'a') {
            linenoiseAddCompletion(lc, "add line <name> <x1> <y1> <x2> <y2>");
            linenoiseAddCompletion(lc, "add circle <name> <x> <y> <radius>");
            linenoiseAddCompletion(lc, "add rectangle <name> <x> <y> <width> <height>");
        } else if (buf[0] == 's') {
            linenoiseAddCompletion(lc, "scale <factor>");
        } else if (buf[0] == 'm') {
            linenoiseAddCompletion(lc, "move <name> <dx> <dy>");
        } else if (buf[0] == 'r') {
            linenoiseAddCompletion(lc, "remove <name>");
        } else if (buf[0] == 'e') {
            linenoiseAddCompletion(lc, "exit");
        } else if (buf[0] == 'h') {
            linenoiseAddCompletion(lc, "help");
        }
    });

    while (true) {
        char* line = linenoise("command: ");
        if (line == nullptr) {
            break;
        }
        if (line[0] != '\0') {
            std::istringstream iss(line);
            iss >> command;
            if (command == "add") {
                std::string type, name;
                double x1, y1, x2, y2, radius, width, height;
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
            else if (command == "exit") {
                break;
            }
            else if (command == "help") {
                print_help();
            }
        }
    }
}
