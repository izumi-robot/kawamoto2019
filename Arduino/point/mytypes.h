#ifndef MYTYPES_H
#define MYTYPES_H

#ifdef ARDUINO

#include <ArxContainer.h>
#include <ArxTypeTraits.h>
#include <ArxStringUtils.h>

#else /* ARDUINO */

#include <initializer_list>
#include <type_traits>
#include <string>

using std::size_t;
using String = std::string;

#endif /* ARDUINO */


#define T_LIST T(&)[2]

template<class T>
class MyPoint {
private:
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    T x, y;
    MyPoint();
    MyPoint(const T&, const T&);
    MyPoint(const MyPoint&);
    MyPoint(const T_LIST);
    MyPoint(std::initializer_list<T>);

    MyPoint& operator=(const MyPoint&);
    MyPoint& operator=(const T_LIST);

    /* define array subscription (a.k.a. []) */
    const T& operator[](size_t) const;
    T& operator[](size_t);

    /* define operation */
    inline MyPoint operator+(const MyPoint&) const;
    inline MyPoint operator-(const MyPoint&) const;
    MyPoint& operator+=(const MyPoint&);
    MyPoint& operator-=(const MyPoint&);
    inline MyPoint operator+(const T_LIST) const;
    inline MyPoint operator-(const T_LIST) const;
    MyPoint& operator+=(const T_LIST);
    MyPoint& operator-=(const T_LIST);
    inline MyPoint operator*(const MyPoint&) const;
    inline MyPoint operator*(const T_LIST) const;
    inline MyPoint operator*(const T&) const;
    MyPoint& operator*=(const MyPoint&);
    MyPoint& operator*=(const T_LIST);
    MyPoint& operator*=(const T&);
    String to_string();
};

#endif /* MYTYPES_H */