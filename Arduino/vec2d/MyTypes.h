#ifndef MYTYPES_H
#define MYTYPES_H

//namespace {

#ifdef ARDUINO

#include <ArxContainer.h>
#include <ArxTypeTraits.h>
#include <ArxStringUtils.h>

#else /* def ARDUINO */

#include <initializer_list>
#include <type_traits>
#include <string>

using std::size_t;
using String = std::string;

#endif /* def ARDUINO */

#define T_LIST T(&)[2]
#define TMP template <class T>
#define T_VEC2D robo::Vector2D<T>

//}

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
    T mag();
};

};

TMP inline T_VEC2D operator+(const T_VEC2D&, const T_VEC2D&);
TMP inline T_VEC2D operator-(const T_VEC2D&, const T_VEC2D&);
TMP inline T_VEC2D operator*(const T_VEC2D&, const T_VEC2D&);
TMP T_VEC2D& operator+=(T_VEC2D&, const T_VEC2D&);
TMP T_VEC2D& operator-=(T_VEC2D&, const T_VEC2D&);
TMP T_VEC2D& operator*=(T_VEC2D&, const T_VEC2D&);

TMP inline T_VEC2D operator+(const T_VEC2D&, const T_LIST);
TMP inline T_VEC2D operator-(const T_VEC2D&, const T_LIST);
TMP inline T_VEC2D operator*(const T_VEC2D&, const T_LIST);
TMP T_VEC2D& operator+=(T_VEC2D&, const T_LIST);
TMP T_VEC2D& operator-=(T_VEC2D&, const T_LIST);
TMP T_VEC2D& operator*=(T_VEC2D&, const T_LIST);

TMP inline T_VEC2D operator*(const T_VEC2D&, const T&);
TMP T_VEC2D& operator*=(const T_VEC2D&, const T&);

#endif /* MYTYPES_H */
