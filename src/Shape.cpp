#include "../include/Shape.h"
#include "../include/Line.h"
#include "../include/Circle.h"
#include "../include/Rectangle.h"
#include "../include/Parallelogram.h"

// std::shared_ptr<Shape> Shape::load(std::ifstream& input_file) {
//     std::string type;
//     input_file >> type;
//     if (type == "Line") {
//         return Line::load(input_file);
//     }
//     else if (type == "Circle") {
//         return Circle::load(input_file);
//     }
//     else if (type == "Rectangle") {
//         return Rectangle::load(input_file);
//     }
//     else if (type == "Parallelogram") {
//         return Parallelogram::load(input_file);
//     }
//     return nullptr;
// }

std::shared_ptr<Shape> Shape::load(const json& shape_json) {
    std::string type = shape_json["type"];
    if (type == "line") {
        return Line::load(shape_json);
    } else if (type == "circle") {
        return Circle::load(shape_json);
    } else if (type == "rectangle") {
        return Rectangle::load(shape_json);
    } else if (type == "parallelogram") {
        return Parallelogram::load(shape_json);
    }
    return nullptr;
}
