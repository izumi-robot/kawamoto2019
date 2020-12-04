#include "mytypes.h"

#ifdef ARDUINO

#define TO_STR(_v_) arx::str::to_string(_v_)

#else /* ARDUINO */

#include <iostream>
#define TO_STR(_v_) std::to_string(_v_)

int main() {
    MyPoint<int> p1(1, 2), p2{2, 3};
    int l[] = {-1, -4};
    //MyPoint<std::vector<int>> p1({1, 2}, {3, 4});   <- COMPILE ERROR!
    std::cout << (p1 * p2 + l).to_string() << std::endl; // (1, 2)
}

#endif /* ARDUINO */

#define TEMPLATE(_type_) template <class T> _type_ MyPoint<T>
#define TEMPLATE_ template <class T> MyPoint<T>

// _tor_ : operator
#define OP_POINT(_tor_) MyPoint<T>(this->x _tor_ other.x, this->y _tor_ other.y)
#define OP_LIST(_tor_) MyPoint<T>(this->x _tor_ other[0], this->y _tor_ other[1])

#define T_LIST_(_name_) T(&_name_)[2]


TEMPLATE_::MyPoint() : x(0), y(0) {}
TEMPLATE_::MyPoint(const T &x, const T &y) : x(x), y(y) {}
TEMPLATE_::MyPoint(const MyPoint<T>& p) {
    this->x = p.x;
    this->y = p.y;
}
TEMPLATE_::MyPoint(const T_LIST_(p)) {
    this->x = p[0];
    this->y = p[1];
}
TEMPLATE_::MyPoint(std::initializer_list<T> init) {
    auto beg = init.begin();
    this->x = *beg;
    this->y = *(beg + 1);
}

TEMPLATE(MyPoint<T>&)::operator=(const MyPoint<T>& tmp) {
    this->x = tmp.x;
    this->y = tmp.y;
    return *this;
}
TEMPLATE(MyPoint<T>&)::operator=(const T_LIST_(data)) {
    this->x = data[0];
    this->y = data[1];
    return *this;
}

/* define array subscription (a.k.a. []) */
TEMPLATE(const T&)::operator[](size_t index) const {
    if (index == 1) {
        return this->y;
    }
    return this->x;
}
TEMPLATE(T&)::operator[](size_t index) {
    if (index == 1) {
        return this->y;
    }
    return this->x;
}

/* define operation */
TEMPLATE(inline MyPoint<T>)::operator+(const MyPoint<T>& other) const {
    // MyPoint<T>(this->x + other.x, this->y + other.y)
    return OP_POINT(+);
}
TEMPLATE(inline MyPoint<T>)::operator-(const MyPoint<T>& other) const {
    return OP_POINT(-);
}
TEMPLATE(MyPoint<T>&)::operator+=(const MyPoint<T>& other) {
    *this = OP_POINT(+);
    return *this;
}
TEMPLATE(MyPoint<T>&)::operator-=(const MyPoint<T>& other) {
    *this = OP_POINT(-);
    return *this;
}
TEMPLATE(inline MyPoint<T>)::operator+(const T_LIST_(other)) const {
    // MyPoint<T>(this->x + other[0], this->y + other[1])
    return OP_LIST(+);
}
TEMPLATE(inline MyPoint<T>)::operator-(const T_LIST_(other)) const {
    return OP_LIST(-);
}
TEMPLATE(MyPoint<T>&)::operator+=(const T_LIST_(other)) {
    *this = OP_LIST(+);
    return *this;
}
TEMPLATE(MyPoint<T>&)::operator-=(const T_LIST_(other)) {
    *this = OP_LIST(-);
    return *this;
}
TEMPLATE(inline MyPoint<T>)::operator*(const MyPoint<T>& other) const {
    // (x, y)(p, q) = (x*p, y*q)
    return OP_POINT(*);
}
TEMPLATE(inline MyPoint<T>)::operator*(const T_LIST_(other)) const {
    return OP_LIST(*);
}
TEMPLATE(inline MyPoint<T>)::operator*(const T& val) const {
    return MyPoint<T>(this->x * val, this->y * val);
}
TEMPLATE(MyPoint<T>&)::operator*=(const MyPoint<T>& other) {
    *this = OP_POINT(*);
    return *this;
}
TEMPLATE(MyPoint<T>&)::operator*=(const T_LIST_(other)) {
    *this = OP_LIST(*);
    return *this;
}
TEMPLATE(MyPoint<T>&)::operator*=(const T& val) {
    this->x *= val;
    this->y *= val;
    return *this;
}

TEMPLATE(String)::to_string() {
    String s = "(" + TO_STR(this->x) + ", " + TO_STR(this->y) + ")";
    return s;
}
