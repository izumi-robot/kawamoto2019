/**
 * @file vec2d.h
 * @brief 自作のベクトル型
 */

#pragma once

#ifndef ROBO2019_VEC2D_H
#define ROBO2019_VEC2D_H

#ifdef ARDUINO

#include <ArxTypeTraits.h>
#include <ArxContainer.h>

#define T_LIST T(&)[2]

#define T_VEC2D robo::Vector2D<T>
#define TMP template <class T>

// _tor_ : operator
#define OP_VEC(_lh_, _rh_, _tor_) T_VEC2D(_lh_.x _tor_ _rh_.x, _lh_.y _tor_ _rh_.y)
#define OP_LIST(_lh_, _ls_, _tor_) T_VEC2D(_lh_.x _tor_ _ls_[0], _lh_.y _tor_ _ls_[1])

#define T_LIST_(_name_) T(&_name_)[2]

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo {

/**
 * @class Vector2D
 * @brief 自作のベクトル型
 * @tparam T 成分の型。算術型でなければならない
 * @details
        実装している演算
 */
template<class T> class Vector2D
{
private: // static part
    static_assert(std::is_arithmetic<T>::value, "must be a number type");
public:
    /**
     * @fn Vector2D from_polar_coord(const double &angle, const T &magnitude)
     * @brief 極形式から座標形式のベクトルを作成する
     * @param[in] angle 偏角。ラジアンで指定する点に注意
     * @param[in] magnitude 大きさ
     * @return 座標形式に変換したベクトル
     * @details
            返されるベクトルの式
            (x, y) = (cos(angle) * magnitude, sin(angle) * magnitude)
     */
    static Vector2D from_polar_coord(const double &, const T &);
    /**
     * @fn Vector2D from_polar_coord(Vector2D *dst, const double &angle, const T &magnitude)
     * @brief 極形式から座標形式のベクトルを作成する
     * @param[in] angle 偏角。ラジアンで指定する点に注意
     * @param[in] magnitude 大きさ
     * @param[out] dst 座標形式に変換したベクトル
     * @details
            返されるベクトルの式
            (x, y) = (cos(angle) * magnitude, sin(angle) * magnitude)
     */
    static void from_polar_coord(Vector2D *, const double &, const T &);

public: // nonstatic part
    //! ベクトルのx成分
    T x;
    //! ベクトルのy成分
    T y;

    /**
     * @brief デフォルトのコンストラクタ
     * @details x, yともに0で初期化される
     */
    Vector2D() : x(0), y(0) {}
    /**
     * @brief x, y成分を指定して初期化
     */
    Vector2D(const T &x, const T &y) : x(x), y(y) {}
    /**
     * @brief コピーコンストラクタ
     */
    Vector2D(const Vector2D &p) : x(p.x), y(p.y) {}
    /**
     * @brief 配列から初期化
     * @details 0番の要素がx、1番の要素がy
     */
    Vector2D(const T_LIST_(p)) : x(p[0]), y(p[1]) {}
    /**
     * @brief リスト初期化
     */
    Vector2D(const std::initializer_list<T> &init)
    {
        auto beg = init.begin();
        x = *beg;
        y = *(beg + 1);
    }

    // TODO: クラスの説明に書く
    Vector2D& operator=(const Vector2D &);
    Vector2D& operator=(const T_LIST);

    inline const T& operator[](size_t) const;
    inline T& operator[](size_t);

    /**
     * @fn String to_string() const
     * @brief ベクトルの文字列表現を返す
     * @return "(x, y)"
     */
    String to_string() const;
    /**
     * @fn void to_string(String *dst)
     * @brief ベクトルの文字列表現を返す
     * @param[out] dst "(x, y)"
     */
    void to_string(String *);
    /**
     * @fn void to_string(char *dst)
     * @brief ベクトルの文字列表現を返す
     * @param[out] dst "(x, y)"
     * @note 配列の容量チェックは行っていないので注意すること。
     */
    void to_string(char *);

    /**
     * @fn T dot(const Vector2D &v) const
     * @brief ベクトルvとの内積を返す
     * @param[in] v 内積をとるベクトル
     * @return x * v.x + y * v.y
     */
    inline T dot(const Vector2D &) const;
    /**
     * @fn T dot(const T (&tmp)[2]) const
     * @brief 配列tmpをベクトルとみなし、それとの内積を返す
     * @param[in] tmp 内積をとるベクトルの配列形式
     * @return x * tmp[0] + y * tmp[1]
     */
    inline T dot(const T_LIST) const;
    /**
     * @fn T dot(const T &x, const T &y) const
     * @brief ベクトル(x, y)との内積を返す
     * @param[in] x 内積をとるベクトルのx成分
     * @param[in] y 内積をとるベクトルのy成分
     * @return this->x * x + this->y * y
     */
    inline T dot(const T &, const T &) const;

    /**
     * @fn void dot(T *dst, const Vector2D &v)
     * @brief ベクトルvとの内積を返す
     * @param[in] v 内積をとるベクトル
     * @param[out] dst x * v.x + y * v.y
     */
    void dot(T *, const Vector2D &);
    /**
     * @fn void dot(T *dst, const T (&tmp)[2]) const
     * @brief 配列tmpをベクトルとみなし、それとの内積を返す
     * @param[in] tmp 内積をとるベクトルの配列形式
     * @param[out] dst x * tmp[0] + y * tmp[1]
     */
    void dot(T *, const T_LIST);
    /**
     * @fn void dot(T *dst, const T &x, const T &y) const
     * @brief ベクトル(x, y)との内積を返す
     * @param[in] x 内積をとるベクトルのx成分
     * @param[in] y 内積をとるベクトルのy成分
     * @param[out] dst this->x * x + this->y * y
     */
    void dot(T *, const T &, const T &);

    /**
     * @fn double angle() const
     * @brief ベクトルの偏角を返す
     * @return 偏角(ラジアン)
     */
    inline double angle() const;
    /**
     * @fn void angle(double *dst)
     * @brief ベクトルの偏角を返す
     * @param[out] dst 偏角(ラジアン)
     */
    void angle(double *);
    /**
     * @fn double mag() const
     * @brief ベクトルの大きさを返す
     * @return ベクトルの大きさ
     */
    inline double mag() const;
    /**
     * @fn void mag(double *dst)
     * @brief ベクトルの大きさを返す
     * @param[out] dst ベクトルの大きさ
     */
    void mag(double *);
};

//! Vector2D<double>のエイリアス
using V2_double = Vector2D<double>;
//! Vector2D<int>のエイリアス
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
    if (dst == NULL) return;
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
    char buffer[64] = "";
    to_string(buffer);
    return String(buffer);
}
TMP void T_VEC2D::to_string(String *dst)
{
    if (dst == NULL) return;
    char buffer[64] = "";
    to_string(buffer);
    *dst = buffer;
}
TMP void T_VEC2D::to_string(char *dst)
{
    if (dst == NULL) return;
    String x_s = String(x);
    String y_s = String(y);
    sprintf(dst, "(%s, %s)", x_s.c_str(), y_s.c_str());
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
    *dst = atan2(y, x);
}

TMP double T_VEC2D::mag() const
{
    return sqrt(x * x + y * y);
}
TMP void T_VEC2D::mag(double *dst)
{
    if (dst == NULL) return;
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

#undef T_LIST

#undef T_VEC2D
#undef TMP

#undef OP_VEC
#undef OP_LIST

#undef T_LIST_

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */

#endif /* ROBO2019_VEC2D_H */
