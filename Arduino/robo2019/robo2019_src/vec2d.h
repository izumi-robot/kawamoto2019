/**
 * @file vec2d.h
 * @brief 自作のベクトル型
 */

#ifndef ROBO2019_VEC2D_H
#define ROBO2019_VEC2D_H

#ifdef ARDUINO

#include <ArxTypeTraits.h>

#define T_LIST T(&)[2]

#define T_VEC2D robo::Vector2D<T>
#define TMP template <class T>

// _tor_ : operator
#define OP_VEC(_lh_, _rh_, _tor_) T_VEC2D(_lh_.x _tor_ _rh_.x, _lh_.y _tor_ _rh_.y)
#define OP_LIST(_lh_, _ls_, _tor_) T_VEC2D(_lh_.x _tor_ _ls_[0], _lh_.y _tor_ _ls_[1])

#define T_LIST_(_name_) T(&_name_)[2]

namespace robo {

template<class T>
class Vector2D
{
private: // static part
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    static Vector2D from_polar_coord(const double &, const T &);
    static void from_polar_coord(Vector2D *, const double &, const T &);

public: // nonstatic part
    T x, y;

    Vector2D() : x(0), y(0) {}
    Vector2D(const T &x, const T &y)
        : x(x), y(y) {}
    Vector2D(const T_VEC2D &p)
        : x(p.x), y(p.y) {}
    Vector2D(const T_LIST_(p))
        : x(p[0]), y(p[1]) {}
    Vector2D(const std::initializer_list<T> &init)
    {
        auto beg = init.begin();
        x = *beg;
        y = *(beg + 1);
    }

    Vector2D& operator=(const T_VEC2D &);
    Vector2D& operator=(const T_LIST);

    inline const T& operator[](size_t) const;
    inline T& operator[](size_t);

    String to_string() const;
    void to_string(String *);

    inline T dot(const Vector2D &) const;
    inline T dot(const T_LIST) const;
    inline T dot(const T &, const T &) const;
    inline void dot(T *, const Vector2D &);
    inline void dot(T *, const T_LIST);
    inline void dot(T *, const T &, const T &);

    inline double angle() const;
    inline void angle(double *);
    inline double mag() const;
    inline void mag(double *);
};

using V2_double = Vector2D<double>;
using V2_int = Vector2D<int>;

} // namespace robo

TMP T_VEC2D T_VEC2D::from_polar_coord(const double &angle, const T &magnitude)
{
    return T_VEC2D{
        magnitude * cos(angle),
        magnitude * sin(angle)
    };
}
TMP void T_VEC2D::from_polar_coord(T_VEC2D *dst, const double &angle, const T &magnitude)
{
    dst->x = magnitude * cos(angle);
    dst->y = magnitude * sin(angle);
}

TMP T_VEC2D& T_VEC2D::operator=(const T_VEC2D &tmp)
{
    x = tmp.x;
    y = tmp.y;
    return *this;
}

TMP T_VEC2D& T_VEC2D::operator=(const T_LIST_(tmp))
{
    x = tmp[0];
    y = tmp[1];
    return *this;
}

TMP const T& T_VEC2D::operator[](size_t index) const
{
    return index == 1 ? y : x;
}

TMP T& T_VEC2D::operator[](size_t index)
{
    return index == 1 ? y : x;
}

TMP String T_VEC2D::to_string() const
{
    return (
        "(" + String(x) + ", " + String(y) + ")"
    );
}
TMP void T_VEC2D::to_string(String *dst)
{
    *dst = "(" + String(x) + ", " + String(y) + ")";
}

TMP T T_VEC2D::dot(const T_VEC2D &v) const
{
    return x * v.x + y * v.y;
}

TMP T T_VEC2D::dot(const T_LIST_(tmp)) const
{
    return x * tmp[0] + y * tmp[1];
}

TMP T T_VEC2D::dot(const T &x, const T &y) const
{
    return this->x * x + this->y * y;
}

TMP double T_VEC2D::angle() const
{
    return atan2(y, x);
}
TMP void T_VEC2D::angle(double *dst)
{
    *dst = atan2(y, x);
}

TMP double T_VEC2D::mag() const
{
    return sqrt(x * x + y * y);
}
TMP void T_VEC2D::mag(double *dst)
{
    *dst = sqrt(x * x + y * y);
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

TMP inline T_VEC2D operator/(const T_VEC2D &lh, const T_VEC2D &rh) {
    return OP_VEC(lh, rh, /);
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

TMP T_VEC2D& operator/=(T_VEC2D& lh, const T_VEC2D& rh) {
    lh.x /= rh.x;
    lh.y /= rh.y;
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

TMP inline T_VEC2D operator/(const T_VEC2D &lh, const T_LIST_(rh)) {
    return OP_LIST(lh, rh, /);
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

TMP T_VEC2D& operator/=(T_VEC2D &lh, const T_LIST_(rh)) {
    lh.x /= rh[0];
    lh.y /= rh[1];
    return lh;
}

TMP inline T_VEC2D operator*(const T_VEC2D &lh, const T &rh) {
    return T_VEC2D(lh.x * rh, lh.y * rh);
}

TMP inline T_VEC2D operator/(const T_VEC2D &lh, const T &rh) {
    return T_VEC2D(lh.x / rh, lh.y / rh);
}

TMP T_VEC2D& operator*=(T_VEC2D &lh, const T &rh) {
    lh.x *= rh;
    lh.y *= rh;
    return lh;
}

TMP T_VEC2D& operator/=(T_VEC2D &lh, const T &rh) {
    lh.x /= rh;
    lh.y /= rh;
    return lh;
}

TMP bool operator==(const T_VEC2D &lh, const T_VEC2D &rh)
{
    return lh.x == rh.x && lh.y == rh.y;
}

TMP bool operator!=(const T_VEC2D &lh, const T_VEC2D &rh)
{
    return lh.x != rh.x || lh.y != rh.y;
}

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_VEC2D_H */
