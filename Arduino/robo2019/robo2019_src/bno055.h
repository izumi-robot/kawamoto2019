/**
 * @file bno055.h
 * @brief BNO055センサー操作用のクラス定義
 */

#ifndef ROBO2019_BNO055_H
#define ROBO2019_BNO055_H

#ifdef ARDUINO

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


namespace robo {

class BNO_wrapper
{
private:
    //! シングルトンオブジェクト
    static BNO_wrapper _singleton;

    //! bno055を検知したかどうか
    bool _detected;
    //! bno055のインスタンス
    Adafruit_BNO055 _bno;

private:
    // シングルトンにする上で欠かせない部分
    /**
     * @brief コンストラクタ
     */
    BNO_wrapper() : _bno(55) {}
    /**
     * @brief コピーコンストラクタ
     */
    BNO_wrapper(const BNO_wrapper &) : _bno(55) {}
    /**
     * @brief デストラクタ
     */
    ~BNO_wrapper() {}
    /**
     * @brief コピー代入
     */
    BNO_wrapper& operator=(const BNO_wrapper &) {}

public:
    /**
     * @fn BNO_wrapper& instance()
     * @brief シングルトンのインスタンス取得用
     * @return インスタンスの参照
     * @note robo::bno_wrapperに同じ参照が格納されている
     */
    static BNO_wrapper& instance();

    /**
     * @fn void setup();
     * @brief bno055のセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない
     */
    void setup();
    /**
     * @fn double get_direction()
     * @brief 現在向いている方向をラジアンで取得
     * @return 現在向いている方向
     * @note ラジアンの値は、0を最初の向きとして、そこから正回転が反時計回りとなっている
     */
    double get_direction();
    /**
     * @fn void get_direction(double *dst)
     * @brief 現在向いている方向をラジアンで取得
     * @param[out] dst 現在向いている方向
     * @note ラジアンの値は、0を最初の向きとして、そこから正回転が反時計回りとなっている
     */
    void get_direction(double *);
    /**
     * @fn Adafruit_BNO055& bno()
     * @brief 保持しているbno055のインスタンスを取得
     * @return 保持しているbno055のインスタンス
     */
    Adafruit_BNO055& bno();
};

BNO_wrapper BNO_wrapper::_singleton;

BNO_wrapper& BNO_wrapper::instance()
{
    return BNO_wrapper::_singleton;
}

void BNO_wrapper::setup()
{
    _detected = _bno.begin();
    _bno.setExtCrystalUse(true);
}

double BNO_wrapper::get_direction()
{
    if (!_detected) { return 0.; }
    double dir_degree = _bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
    double dir_radian = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
    return dir_radian;
}
void BNO_wrapper::get_direction(double *dst)
{
    if (dst == NULL) return;
    double &res = *dst;
    if (!_detected) { res = 0.; }
    double dir_degree = _bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
    res = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
}

Adafruit_BNO055& BNO_wrapper::bno()
{
    return this->_bno;
}

BNO_wrapper &bno_wrapper = BNO_wrapper::instance();

class _BNO055 : public Adafruit_BNO055
{
private:
    //! シングルトンオブジェクト
    static _BNO055 _singleton;
    //! bnoを検知したかどうか
    bool _detected;

private:
    // シングルトンにする上で欠かせない部分
    /**
     * @brief コンストラクタ
     */
    _BNO055() : Adafruit_BNO055(55) {}
    /**
     * @brief コピーコンストラクタ
     */
    _BNO055(const _BNO055 &) : Adafruit_BNO055(55) {}
    /**
     * @brief デストラクタ
     */
    ~_BNO055() {}
    /**
     * @brief コピー代入
     */
    _BNO055& operator=(const _BNO055 &) {}

public:
    /**
     * @fn _BNO055& instance()
     * @brief シングルトンのインスタンスを取得する
     * @return インスタンスの参照
     * @note robo::_bno055に同じ参照が格納されている
     */
    static _BNO055& instance();

    /**
     * @fn void setup();
     * @brief bno055のセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない
     */
    void setup();
    /**
     * @fn double get_direction()
     * @brief 現在向いている方向をラジアンで取得
     * @return dst 現在向いている方向
     */
    double get_direction();
    /**
     * @fn void get_direction(double *dst)
     * @brief 現在向いている方向をラジアンで取得
     * @param[out] dst 現在向いている方向
     * @note ラジアンの値は、0を最初の向きとして、そこから正回転が反時計回りとなっている
     */
    void get_direction(double *);
};

_BNO055 _BNO055::_singleton;

_BNO055& _BNO055::instance()
{
    return _singleton;
}

void _BNO055::setup()
{
    _detected = Adafruit_BNO055::begin();
    Adafruit_BNO055::setExtCrystalUse(true);
}

double _BNO055::get_direction()
{
    if (!_detected) { return 0.; }
    double dir_degree = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_EULER).x();
    double dir_radian = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
    return dir_radian;
}
void _BNO055::get_direction(double *dst)
{
    if (dst == NULL) return;
    double &res = *dst;
    if (!_detected) { res = 0.; }
    double dir_degree = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_EULER).x();
    res = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
}

_BNO055 &_bno055 = _BNO055::instance();

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_BNO055_H */