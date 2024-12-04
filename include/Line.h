#include "Shape.h"

class Line : public Shape {
private:
    int _x1, _y1, _x2, _y2;
    std::string _name;
public:
    Line(int x1, int y1, int x2, int y2, const std::string& name);
    void draw(SDL_Renderer* renderer, int scale_x, int scale_y) const override;
    void move(int dx, int dy) override;
    void scale(double factor) override;
    std::string get_name() const override;
};
