#include "Shape.h"

class Circle : public Shape {
private:
    double _x, _y, _radius;
    std::string _name;
public:
    Circle(double x, double y, double radius, const std::string& name);
    void draw(SDL_Renderer* renderer) const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    bool contains(double x, double y) const override;
    std::string get_name() const override;
};