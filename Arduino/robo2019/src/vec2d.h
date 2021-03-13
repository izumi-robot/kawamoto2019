/**
 * @file vec2d_.h
 * @brief 自作のベクトル型
 */

#pragma once

#ifdef ARDUINO

#include <ArxTypeTraits.h>
#include <ArxContainer.h>

#define T_LIST T(&)[2]
#define T_LIST_(_name_) T(&_name_)[2]
#define TMP template<typename T>

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo {

/**
 * @brief 自作のベクトル型
 * @tparam T 成分の型。算術型でなければならない
 * @details
 *  実装している演算(`v`, `v1`, `v2`をベクトル値、`t`をT型の値とする):
 *  - `v1 [+,-,*,/] v2` -> `(v1.x [+,-,*,/] v2.x, v1.y [+,-,*,/] v2.y)`
 *  - `v [*,/] t` -> `(v.x [*,/] t, v.y [*,/] t)` 左右交換も可
 *  `+=`なども同様。
 *  任意のベクトルを要素数2の配列に置き換えることができる。ただし、ベクトルが絡む文脈でなければいけない。
 */
TMP class Vector2D
{
private: // static part
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    /**
     * @brief 極形式から座標形式のベクトルを作成する
     * @param[in] angle 偏角。ラジアンで指定する点に注意
     * @param[in] magnitude 大きさ
     * @return 座標形式に変換したベクトル
     * @details
     *  返されるベクトルの式
     *  `(x, y)` = `(cos(angle) * magnitude, sin(angle) * magnitude)`
     */
    static Vector2D from_polar_coord(const double &angle, const T &magnitude);
    /**
     * @brief 極形式から座標形式のベクトルを作成する
     * @param[in] angle 偏角。ラジアンで指定する点に注意
     * @param[in] magnitude 大きさ
     * @param[out] dst 座標形式に変換したベクトル
     * @details
     *  返されるベクトルの式
     *  `(x, y)` = `(cos(angle) * magnitude, sin(angle) * magnitude)`
     */
    static void from_polar_coord(Vector2D *, const double &angle, const T &magnitude);

public: // instance properties
    //! ベクトルのx成分
    T x;
    //! ベクトルのy成分
    T y;

    /**
     * @brief デフォルトのコンストラクタ
     * @details x, yともに0で初期化される
     */
    Vector2D() : x(0), y(0) {}
    /** @brief x, y成分を指定して初期化 */
    Vector2D(const T &x, const T &y) : x(x), y(y) {}
    /** @brief コピーコンストラクター */
    Vector2D(const Vector2D &p) : x(p.x), y(p.y) {}
    /**
     * @brief 配列から初期化
     * @details 0番の要素がx、1番の要素がy
     */
    Vector2D(const T_LIST_(p)) : x(p[0]), y(p[1]) {}
    /** @brief リスト初期化 */
    Vector2D(const std::initializer_list<T> &init)
    {
        auto beg = init.begin();
        x = *beg;
        y = *(beg + 1);
    }

    Vector2D& operator=(const Vector2D &rh);
    Vector2D& operator=(const T_LIST_(rh));

    inline const T& operator[](size_t index) const;
    inline T& operator[](size_t index);

    /**
     * @brief ベクトルの文字列表現を返す
     * @param[out] dst "(x, y)"
     * @return uint8_t 配列に書き込んだ文字数
     * @note 配列の容量チェックは行っていないので注意すること。
     */
    uint8_t to_string(char *dst);
    /**
     * @brief ベクトルの文字列表現を返す
     * @param[out] dst "(x, y)"
     */
    void to_string(String *dst);
    /**
     * @brief ベクトルの文字列表現を返す
     * @return String "(x, y)"
     */
    String to_string();

    /**
     * @brief ベクトルvとの内積を返す
     * @param[in] v 内積をとるベクトル
     * @return x * v.x + y * v.y
     */
    inline T dot(const Vector2D &v) const;
    /**
     * @brief 配列tmpをベクトルとみなし、それとの内積を返す
     * @param[in] tmp 内積をとるベクトルの配列形式
     * @return x * tmp[0] + y * tmp[1]
     */
    inline T dot(const T_LIST_(tmp)) const;
    /**
     * @brief ベクトル(x, y)との内積を返す
     * @param[in] x 内積をとるベクトルのx成分
     * @param[in] y 内積をとるベクトルのy成分
     * @return this->x * x + this->y * y
     */
    inline T dot(const T &x, const T &y) const;

    /**
     * @brief ベクトルvとの内積を返す
     * @param[in] v 内積をとるベクトル
     * @param[out] dst x * v.x + y * v.y
     */
    void dot(T *dst, const Vector2D &v);
    /**
     * @brief 配列tmpをベクトルとみなし、それとの内積を返す
     * @param[in] tmp 内積をとるベクトルの配列形式
     * @param[out] dst x * tmp[0] + y * tmp[1]
     */
    void dot(T *dst, const T_LIST_(tmp));
    /**
     * @brief ベクトル(x, y)との内積を返す
     * @param[in] x 内積をとるベクトルのx成分
     * @param[in] y 内積をとるベクトルのy成分
     * @param[out] dst this->x * x + this->y * y
     */
    void dot(T *dst, const T &x, const T &y);

    /**
     * @brief ベクトルの偏角を返す
     * @return 偏角(ラジアン)
     */
    inline double angle() const;
    /**
     * @brief ベクトルの偏角を返す
     * @param[out] dst 偏角(ラジアン)
     */
    void angle(double *dst);
    /**
     * @brief ベクトルの大きさを返す
     * @return ベクトルの大きさ
     */
    inline double mag() const;
    /**
     * @brief ベクトルの大きさを返す
     * @param[out] dst ベクトルの大きさ
     */
    void mag(double *dst);
};

//! Vector2D<double>のエイリアス
using V2_double = Vector2D<double>;
//! Vector2D<int>のエイリアス
using V2_int = Vector2D<int>;

} // namespace robo

#undef T_LIST

#define T_VEC2D robo::Vector2D<T>

TMP void T_VEC2D::from_polar_coord(T_VEC2D *dst, const double &angle, const T &magnitude)
{
    if (dst == NULL) return;
    dst->x = magnitude * cos(angle);
    dst->y = magnitude * sin(angle);
}
TMP T_VEC2D T_VEC2D::from_polar_coord(const double &angle, const T &magnitude)
{
    T_VEC2D result;
    from_poler_coord(&result, angle, magnitude);
    return result;
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

#define SUBSCRIBE_IMPL(_type_, _spec_) TMP inline _type_ T_VEC2D::operator[](size_t index) _spec_ { return index ? x : y; }

SUBSCRIBE_IMPL(const T&, const)
SUBSCRIBE_IMPL(T&,)

#undef SUBSCRIBE_IMPL

TMP void T_VEC2D::to_string(char *dst) {
    if (dst == NULL) return;
    if (std::is_floating_point<T>::value) {
        char *ptr = dst;
        *(ptr++) = '(';
        dtostrf(x, 5, 2, ptr); ptr += 5;
        ptr[0] = ','; ptr[1] = ' '; ptr += 2;
        dtostrf(y, 5, 2, ptr); ptr += 5;
        *(ptr++) = ')'; ptr[0] = '\0';
        return ptr - dst;
    } else if (std::is_signed<T>::value) {
        return sprintf(dst, "(%d, %d)", x, y);
    } else {
        return sprintf(dst, "(%u, %u)", x, y);
    }
}
/*
#define ENABLE_IF_V(_cond_) typename std::enable_if<_cond_, void>::type
#define TO_STR T_VEC2D::to_string(char *dst)
TMP ENABLE_IF_V(std::is_floating_point<T>::value) TO_STR {
    if (dst == NULL) return;
    sprintf(dst, "(%f, %f)", x, y);
}
TMP ENABLE_IF_V(std::is_integral<T>::value && std::is_signed<T>::value) TO_STR {
    if (dst == NULL) return;
    sprintf(dst, "(%d, %d)", x, y);
}
TMP ENABLE_IF_V(std::is_integral<T>::value && std::is_unsigned<T>::value) TO_STR {
    if (dst == NULL) return;
    sprintf(dst, "(%u, %u)", x, y);
}
#undef ENABLE_IF_V
#undef TO_STR
*/

TMP void T_VEC2D::to_string(String *dst)
{
    if (dst == NULL) return;
    char buffer[64] = "";
    to_string(buffer);
    *dst = buffer;
}
TMP String T_VEC2D::to_string()
{
    char buffer[64] = "";
    to_string(buffer);
    return String(buffer);
}

TMP T T_VEC2D::dot(const T_VEC2D &v) const { return x * v.x + y * v.y; }
TMP T T_VEC2D::dot(const T_LIST_(tmp)) const { return x * tmp[0] + y * tmp[1]; }
TMP T T_VEC2D::dot(const T &x, const T &y) const { return this->x * x + this->y * y; }

TMP void T_VEC2D::dot(T *dst, const T_VEC2D &v)
{
    if (dst == NULL) return;
    *dst = x * v.x + y * v.y;
}
TMP void T_VEC2D::dot(T *dst, const T_LIST_(tmp))
{
    if (dst == NULL) return;
    *dst = x * tmp[0] + y * tmp[1];
}
TMP void T_VEC2D::dot(T *dst, const T &x, const T &y)
{
    if (dst == NULL) return;
    *dst = this->x * x + this->y * y;
}

TMP double T_VEC2D::angle() const
{
    return atan2(y, x);
}
TMP void T_VEC2D::angle(double *dst)
{
    if (dst == NULL) return;
    *dst = angle();
}

TMP double T_VEC2D::mag() const
{
    return sqrt(x * x + y * y);
}
TMP void T_VEC2D::mag(double *dst)
{
    if (dst == NULL) return;
    *dst = mag();
}

#define IM4(_mc_) _mc_(+) _mc_(-) _mc_(*) _mc_(/)
#define IM2(_mc_) _mc_(*) _mc_(/)

// operator(Vec2D, Vec2D)
#define OP_IMPL(_op_) TMP inline T_VEC2D operator _op_ (const T_VEC2D &lh, const T_VEC2D &rh) {\
    return T_VEC2D(lh.x _op_ rh.x, lh.y _op_ rh.y); }

IM4(OP_IMPL)

#undef OP_IMPL

#define IOP_IMPL(_op_) TMP T_VEC2D& operator _op_ ## = (T_VEC2D &lh, const T_VEC2D &rh) {\
    lh.x _op_ ## = rh.x; lh.y _op_ ## = rh.y;\
    return lh; }

IM4(IOP_IMPL)

#undef IOP_IMPL

// operator(Vec2D, T (&)[2])
#define OP_IMPL(_op_) TMP inline T_VEC2D operator _op_ (const T_VEC2D &lh, const T (&rh)[2]) {\
    return T_VEC2D(lh.x _op_ rh[0], lh.y _op_ rh[1]); }

IM4(OP_IMPL)

#undef OP_IMPL

#define IOP_IMPL(_op_) TMP T_VEC2D& operator _op_ ## = (T_VEC2D &lh, const T (&rh)[2]) {\
    lh.x _op_ ## = rh[0]; lh.y _op_ ## = rh[1];\
    return lh; }

IM4(IOP_IMPL)

#undef IOP_IMPL

// operator(T (&)[2], Vec2D)
#define OP_IMPL(_op_) TMP inline T_VEC2D operator _op_ (const T (&lh)[2], const T_VEC2D &rh) {\
    return T_VEC2D(lh[0] _op_ rh.x, lh[1] _op_ rh.y); }

IM4(OP_IMPL)

#undef OP_IMPL

// operator(Vec2D, T)
#define OP_IMPL(_op_) TMP inline T_VEC2D operator _op_ (const T_VEC2D &lh, const T &rh) {\
    return T_VEC2D(lh.x _op_ rh, lh.y _op_ rh); }

IM2(OP_IMPL)

#undef OP_IMPL

#define IOP_IMPL(_op_) TMP T_VEC2D& operator _op_ ## = (T_VEC2D &lh, const T &rh) {\
    lh.x _op_ ## = rh; lh.y _op_ ## = rh;\
    return lh; }

IM2(IOP_IMPL)

#undef IOP_IMPL

// operator(T, Vec2D)
#define OP_IMPL(_op_) TMP inline T_VEC2D operator _op_ (const T &lh, const T_VEC2D &rh) {\
    return T_VEC2D(lh _op_ rh.x, lh _op_ rh.y); }

IM2(OP_IMPL)

#undef OP_IMPL

#undef IM4
#undef IM2

TMP inline bool operator==(const T_VEC2D &lh, const T_VEC2D &rh) { return lh.x == rh.x && lh.y == rh.y; }
TMP inline bool operator!=(const T_VEC2D &lh, const T_VEC2D &rh) { return lh.x != rh.x || lh.y != rh.y; }

#undef T_VEC2D
#undef TMP
#undef T_LIST_

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */
