#ifndef MYTYPES_H
#define MYTYPES_H


#ifdef ARDUINO

#include <ArxContainer.h>
#include <ArxTypeTraits.h>
#include <ArxStringUtils.h>

#define TO_STR(_v_) String(_v_)

#else /* => ndef ARDUINO */

#include <initializer_list>
#include <type_traits>
#include <iostream>
#include <cmath>
#include <string>

using std::size_t;
using String = std::string;

using std::sqrt;
using std::pow;
using std::atan2;

#define TO_STR(_v_) std::to_string(_v_)

#endif /* ARDUINO */


#define T_LIST T(&)[2]

namespace robo {

template<class T>
class Vector2D {
private:
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    T x, y;
    Vector2D();
    Vector2D(const T&, const T&);
    Vector2D(const Vector2D&);
    Vector2D(const T_LIST);
    Vector2D(std::initializer_list<T>);

    Vector2D& operator=(const Vector2D&);
    Vector2D& operator=(const T_LIST);

    /* define array subscription (a.k.a. []) */
    const T& operator[](size_t) const;
    T& operator[](size_t);

    String to_string();
    T angle();
    T length();
};

}

#define T_VEC2D robo::Vector2D<T>
#define TMP template <class T>
#define TEMPLATE(_type_) TMP _type_ T_VEC2D
#define TEMPLATE_ TMP T_VEC2D

// _tor_ : operator
#define OP_VEC(_lh_, _rh_, _tor_) T_VEC2D(_lh_.x _tor_ _rh_.x, _lh_.y _tor_ _rh_.y)
#define OP_LIST(_lh_, _ls_, _tor_) T_VEC2D(_lh_.x _tor_ _ls_[0], _lh_.y _tor_ _ls_[1])

#define T_LIST_(_name_) T(&_name_)[2]

TEMPLATE_::Vector2D() : x(0), y(0) {}

TEMPLATE_::Vector2D(const T &x, const T &y) : x(x), y(y) {}

TEMPLATE_::Vector2D(const T_VEC2D& p) {
    this->x = p.x;
    this->y = p.y;
}

TEMPLATE_::Vector2D(const T_LIST_(p)) {
    this->x = p[0];
    this->y = p[1];
}

TEMPLATE_::Vector2D(std::initializer_list<T> init) {
    auto beg = init.begin();
    this->x = *beg;
    this->y = *(beg + 1);
}

TEMPLATE(T_VEC2D&)::operator=(const T_VEC2D& tmp) {
    this->x = tmp.x;
    this->y = tmp.y;
    return *this;
}

TEMPLATE(T_VEC2D&)::operator=(const T_LIST_(data)) {
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

TMP inline T_VEC2D operator+(const T_VEC2D &lh, const T_VEC2D &rh) {
    return OP_VEC(lh, rh, +);
}

TMP inline T_VEC2D operator-(const T_VEC2D &lh, const T_VEC2D &rh) {
    return OP_VEC(lh, rh, -);
}
TMP inline T_VEC2D operator*(const T_VEC2D &lh, const T_VEC2D &rh) {
    return OP_VEC(lh, rh, *);
}

TMP T_VEC2D& operator+=(T_VEC2D& lh, const T_VEC2D& rh) {
    lh.x += rh.x;
    lh.y += rh.y;
    return lh;
}

TMP T_VEC2D& operator-=(T_VEC2D& lh, const T_VEC2D& rh) {
    lh.x -= rh.x;
    lh.y -= rh.y;
    return lh;
}

TMP T_VEC2D& operator*=(T_VEC2D& lh, const T_VEC2D& rh) {
    lh.x *= rh.x;
    lh.y *= rh.y;
    return lh;
}

TMP inline T_VEC2D operator+(const T_VEC2D &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, +);
}

TMP inline T_VEC2D operator-(const T_VEC2D &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, -);
}

TMP inline T_VEC2D operator*(const T_VEC2D &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, *);
}

TMP T_VEC2D& operator+=(T_VEC2D &lh, const T_LIST_(rh)) {
    lh.x += rh[0];
    lh.y += rh[1];
    return lh;
}

TMP T_VEC2D& operator-=(T_VEC2D &lh, const T_LIST_(rh)) {
    lh.x -= rh[0];
    lh.y -= rh[1];
    return lh;
}

TMP T_VEC2D& operator*=(T_VEC2D &lh, const T_LIST_(rh)) {
    lh.x *= rh[0];
    lh.y *= rh[1];
    return lh;
}

TMP inline T_VEC2D operator*(const T_VEC2D &lh, const T &rh) {
    return T_VEC2D(lh.x * rh, lh.y * rh);
}

TMP T_VEC2D& operator*=(T_VEC2D &lh, const T &rh) {
    lh.x *= rh;
    lh.y *= rh;
    return lh;
}

TEMPLATE(String)::to_string() {
    String s = "(" + TO_STR(this->x) + ", " + TO_STR(this->y) + ")";
    return s;
}

TEMPLATE(T)::angle() {
    return T(atan2(this->y, this->x));
}

TEMPLATE(T)::length() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}


#ifndef ARDUINO

int main() {
    robo::Vector2D<int> p1(1, 2), p2{2, 3};
    int l[] = {-1, -4};
    //Vector2D<std::vector<int>> p1({1, 2}, {3, 4});   <- COMPILE ERROR!
    std::cout << (p1 * p2 + l).to_string() << std::endl; // (1, 2)
    std::cout << robo::Vector2D<int>{3, 4}.mag() << std::endl; // 5
}

#endif /* ARDUINO */


#endif /* MYTYPES_H */
