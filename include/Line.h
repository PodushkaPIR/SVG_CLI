#include "Shape.h"

class Line : public Shape {
private:
    double _x1, _y1, _x2, _y2;
    std::string _name;
public:
    Line(double x1, double y1, double x2, double y2, const std::string& name);
    void draw(SDL_Renderer* renderer) const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    bool contains(double x, double y) const override;
    void save(std::ofstream& out_file) const override;
    static std::shared_ptr<Shape> load(std::ifstream& input_file);
    std::string get_name() const override;
};
