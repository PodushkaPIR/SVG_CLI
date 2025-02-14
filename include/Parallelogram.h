#include "Shape.h"

class Parallelogram : public Shape {
private:
    double _x, _y, _skew, _width, _height;
    std::string _name;
public:
    Parallelogram(double x, double y, double skew, double width, double height, const std::string& name);
    void draw(SDL_Renderer* renderer) const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    bool contains(double px, double py) const override;
    void save(std::ofstream& out_file) const override;
    static std::shared_ptr<Shape> load(std::ifstream& input_file);
    std::string get_name() const override;
};

