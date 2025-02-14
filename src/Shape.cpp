#include "../include/Shape.h"
#include "../include/Line.h"
#include "../include/Circle.h"
#include "../include/Rectangle.h"
#include "../include/Parallelogram.h"

std::shared_ptr<Shape> Shape::load(std::ifstream& input_file) {
    std::string type;
    input_file >> type;
    if (type == "Line") {
        return Line::load(input_file);
    }
    else if (type == "Circle") {
        return Circle::load(input_file);
    }
    else if (type == "Rectangle") {
        return Rectangle::load(input_file);
    }
    else if (type == "Parallelogram") {
        return Parallelogram::load(input_file);
    }
    return nullptr;
}


// std::shared_ptr<Shape> Shape::load(std::ifstream& input_file) {
//     std::string type;
//     input_file >> type;
//     // std::cout << "\n" << "Type: " << type << "\n";
//     if (type != "Line" || type != "Circle" || type != "Rectangle") {
//         return nullptr;
//     }
//     double x1, y1, x2, y2, radius, width, height;
//     std::string name;
//     if (type == "Line") {
//         input_file >> x1 >> y1 >> x2 >> y2 >> name;
//         // std::cout << "Params: " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << name << "\n";
//         return std::make_shared<Line>(x1, y1, x2, y2, name);
//     }
//     else if (type == "Circle") {
//         input_file >> x1 >> y1 >> radius >> name;
//         return std::make_shared<Circle>(x1, y1, radius, name);
//     }
//     else if (type == "Rectangle") {
//         input_file >> x1 >> y1 >> width >> height >> name;
//         return std::make_shared<Line>(x1, y1, width, height, name);
//     }
//     return nullptr;
// }
