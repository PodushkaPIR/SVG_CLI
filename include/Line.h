#include "Shape.h"

class Line : public Shape {
private:
    int _x1, _y1, _x2, _y2;
    std::string _name;
public:
    Line(double x1, double y1, double x2, double y2, const std::string& name);
    void draw(cairo_t* cr) const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string get_name() const override;
};
