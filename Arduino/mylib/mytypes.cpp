#include "MyTypes.h"

#ifdef ARDUINO

#define TO_STR(_v_) arx::str::to_string(_v_)

#else /* ARDUINO */

#include <iostream>
#include <string>
#define TO_STR(_v_) std::to_string(_v_)

int main() {
    MyPoint<int> p1(1, 2), p2{2, 3};
    int l[] = {-1, -4};
    //MyPoint<std::vector<int>> p1({1, 2}, {3, 4});   <- COMPILE ERROR!
    std::cout << (p1 * p2 + l).to_string() << std::endl; // (1, 2)
}

#endif /* ARDUINO */

#define TEMPLATE(_type_) TMP _type_ T_MPOINT
#define TEMPLATE_ TMP T_MPOINT

// _tor_ : operator
#define OP_POINT(_lh_, _rh_, _tor_) T_MPOINT(_lh_.x _tor_ _rh_.x, _lh_.y _tor_ _rh_.y)
#define OP_LIST(_lh_, _ls_, _tor_) T_MPOINT(_lh_.x _tor_ _ls_[0], _lh_.y _tor_ _ls_[1])

#define T_LIST_(_name_) T(&_name_)[2]


TEMPLATE_::MyPoint() : x(0), y(0) {}

TEMPLATE_::MyPoint(const T &x, const T &y) : x(x), y(y) {}

TEMPLATE_::MyPoint(const T_MPOINT& p) {
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

TEMPLATE(T_MPOINT&)::operator=(const T_MPOINT& tmp) {
    this->x = tmp.x;
    this->y = tmp.y;
    return *this;
}

TEMPLATE(T_MPOINT&)::operator=(const T_LIST_(data)) {
    this->x = data[0];
    this->y = data[1];
    return *this;
}

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

TMP inline T_MPOINT operator+(const T_MPOINT &lh, const T_MPOINT &rh) {
    return OP_POINT(lh, rh, +);
}

TMP inline T_MPOINT operator-(const T_MPOINT &lh, const T_MPOINT &rh) {
    return OP_POINT(lh, rh, -);
}

TMP inline T_MPOINT operator*(const T_MPOINT &lh, const T_MPOINT &rh) {
    return OP_POINT(lh, rh, *);
}

TMP T_MPOINT& operator+=(T_MPOINT& lh, const T_MPOINT& rh) {
    lh.x += rh.x;
    lh.y += rh.y;
    return lh;
}

TMP T_MPOINT& operator-=(T_MPOINT& lh, const T_MPOINT& rh) {
    lh.x -= rh.x;
    lh.y -= rh.y;
    return lh;
}

TMP T_MPOINT& operator*=(T_MPOINT& lh, const T_MPOINT& rh) {
    lh.x *= rh.x;
    lh.y *= rh.y;
    return lh;
}

TMP inline T_MPOINT operator+(const T_MPOINT &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, +);
}

TMP inline T_MPOINT operator-(const T_MPOINT &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, -);
}

TMP inline T_MPOINT operator*(const T_MPOINT &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, *);
}

TMP T_MPOINT& operator+=(T_MPOINT &lh, const T_LIST_(rh)) {
    lh.x += rh[0];
    lh.y += rh[1];
    return lh;
}

TMP T_MPOINT& operator-=(T_MPOINT &lh, const T_LIST_(rh)) {
    lh.x -= rh[0];
    lh.y -= rh[1];
    return lh;
}

TMP T_MPOINT& operator*=(T_MPOINT &lh, const T_LIST_(rh)) {
    lh.x *= rh[0];
    lh.y *= rh[1];
    return lh;
}

TMP inline T_MPOINT operator*(const T_MPOINT &lh, const T &rh) {
    return T_MPOINT(lh.x * rh, lh.y * rh);
}

TMP T_MPOINT& operator*(T_MPOINT &lh, const T &rh) {
    lh.x *= rh;
    lh.y *= rh;
    return lh;
}

TEMPLATE(String)::to_string() {
    String s = "(" + TO_STR(this->x) + ", " + TO_STR(this->y) + ")";
    return s;
}
