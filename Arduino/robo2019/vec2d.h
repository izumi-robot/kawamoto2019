#ifndef MYTYPES_H
#define MYTYPES_H


#ifdef ARDUINO

#include <ArxContainer.h>
#include <ArxTypeTraits.h>
#include <ArxStringUtils.h>

#define TO_STR(_v_) String(_v_)

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */


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
private:
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    static Vector2D from_polar_coord(const double &angle, const T &magnitude)
    {
        T x = magnitude * cos(angle), y = magnitude * sin(angle);
        return Vector2D<T>{x, y};
    }

    T x, y;

    Vector2D() : x(0), y(0) {}

    Vector2D(const T &x, const T &y)
        : x(x), y(y) {}

    Vector2D(const T_VEC2D &p)
    {
        this->x = p.x;
        this->y = p.y;
    }

    Vector2D(const T_LIST_(p))
    {
        this->x = p[0];
        this->y = p[1];
    }

    Vector2D(std::initializer_list<T> init)
    {
        auto beg = init.begin();
        this->x = *beg;
        this->y = *(beg + 1);
    }

    /* define array subscription (a.k.a. []) */

    Vector2D& operator=(const T_VEC2D &tmp)
    {
        this->x = tmp.x;
        this->y = tmp.y;
        return *this;
    }

    Vector2D& operator=(const T_LIST_(tmp))
    {
        this->x = tmp[0];
        this->y = tmp[1];
        return *this;
    }

    const T& operator[](size_t index) const
    {
        if (index == 1) {
            return this->y;
        }
        return this->x;
    }

    T& operator[](size_t index)
    {
        if (index == 1) {
            return this->y;
        }
        return this->x;
    }

    String to_string() const
    {
        return "(" + String(this->x) + ", " + String(this->y) + ")";
    }

    inline T dot(const Vector2D &v) const
    {
        return this->x * v.x + this->y * v.y;
    }

    inline T dot(const T_LIST_(tmp)) const
    {
        return this->x * tmp[0] + this->y * tmp[1];
    }

    inline T dot(const T &x, const T &y) const
    {
        return this->x * x + this->y * y;
    }

    double angle() const
    {
        return atan2(this->y, this->x);
    }

    double mag() const
    {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }
};

using V2_double = Vector2D<double>;
using V2_int = Vector2D<int>;

} // namespace robo

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

#endif /* MYTYPES_H */
