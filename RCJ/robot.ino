#include <vector> // vector class
#include <utility> // pair, make_pair
#include <type_traits>

class XYPoint {
private:

public:
    double x, y;

    XYPoint() : x(0.0), y(0.0) {}

    template<class T>
    XYPoint(T x, T y) : x((double)x), y((double)y) {}

    XYPoint operator+(XYPoint const& other) {
        XYPoint result(this->x + other.x, this->y + other.y);
        return result;
    }

    XYPoint operator-(XYPoint const& other) {
        XYPoint result(this->x - other.x, this->y - other.y);
        return result;
    }

    XYPoint operator*()
}

class Robot {

}