#ifndef MYTYPES_H
#define MYTYPES_H

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
#define T_MPOINT MyPoint<T>

template<class T>
class MyPoint {
private:
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    T x, y;
    MyPoint();
    MyPoint(const T&, const T&);
    MyPoint(const MyPoint<T>&);
    MyPoint(const T_LIST);
    MyPoint(std::initializer_list<T>);

    MyPoint& operator=(const MyPoint<T>&);
    MyPoint& operator=(const T_LIST);

    /* define array subscription (a.k.a. []) */
    const T& operator[](size_t) const;
    T& operator[](size_t);

    String to_string();
};

TMP inline T_MPOINT operator+(const T_MPOINT&, const T_MPOINT&);
TMP inline T_MPOINT operator-(const T_MPOINT&, const T_MPOINT&);
TMP inline T_MPOINT operator*(const T_MPOINT&, const T_MPOINT&);
TMP T_MPOINT& operator+=(T_MPOINT&, const T_MPOINT&);
TMP T_MPOINT& operator-=(T_MPOINT&, const T_MPOINT&);
TMP T_MPOINT& operator*=(T_MPOINT&, const T_MPOINT&);

TMP inline T_MPOINT operator+(const T_MPOINT&, const T_LIST);
TMP inline T_MPOINT operator-(const T_MPOINT&, const T_LIST);
TMP inline T_MPOINT operator*(const T_MPOINT&, const T_LIST);
TMP T_MPOINT& operator+=(T_MPOINT&, const T_LIST);
TMP T_MPOINT& operator-=(T_MPOINT&, const T_LIST);
TMP T_MPOINT& operator*=(T_MPOINT&, const T_LIST);

TMP inline T_MPOINT operator*(const T_MPOINT&, const T&);
TMP T_MPOINT& operator*=(const T_MPOINT&, const T&);

#endif /* MYTYPES_H */
