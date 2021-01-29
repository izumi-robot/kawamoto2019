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

#include "util.h"

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo {

/**
 * @class BNO_wrapper
 * @brief BNO055操作用のクラス
 * @note シングルトン
 */
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

//! シングルトンオブジェクトへの参照
BNO_wrapper &bno_wrapper = BNO_wrapper::instance();

/**
 * @class _BNO055
 * @brief Adafruit_BNO055の子クラス
 * @note シングルトン
 */
class _BNO055 : public virtual Adafruit_BNO055, public virtual robo::SingletonBase<_BNO055>
{
    friend class robo::SingletonBase<_BNO055>;
private:
    //! bnoを検知したかどうか
    bool _detected;
    //! 最新の、ジャイロセンサーで算出した方向
    double _last_gyro_dir;
    /**
     * @brief 地磁気のズレ
     * @details `0`が指す向きの、最初の向きとのズレ
     */
    double _geomag_diff;

protected:
    /**
     * @brief コンストラクタ
     */
    _BNO055()
        : Adafruit_BNO055(55), robo::SingletonBase<_BNO055>(),
        _detected(false), _last_gyro_dir(0), _geomag_diff(0) {}

public:
    /**
     * @fn void setup();
     * @brief bno055のセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない
     */
    void setup();
    /**
     * @fn double get_geomag_direction()
     * @brief 現在向いている方向をラジアンで取得
     * @return dst 現在向いている方向
     * @note ラジアンの値は、0を最初の向きとして、そこから正回転が反時計回り
     */
    double get_geomag_direction();
    /**
     * @fn void get_geomag_direction(double *dst)
     * @brief 現在向いている方向をラジアンで取得
     * @param[out] dst 現在向いている方向
     * @note ラジアンの値は、0を最初の向きとして、そこから正回転が反時計回り
     */
    void get_geomag_direction(double *);

    /**
     * @fn bool detected()
     * @brief bnoが検知されたかどうか
     * @return 検知されたらtrue
     */
    inline bool detected();

    /**
     * @fn double update_gyro_dir();
     */
    double update_gyro_dir();
};

void _BNO055::setup()
{
    _detected = Adafruit_BNO055::begin();
    Adafruit_BNO055::setExtCrystalUse(true);
}

double _BNO055::get_geomag_direction()
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
void _BNO055::get_geomag_direction(double *dst)
{
    if (dst == NULL) return;
    double &res = *dst;
    if (!_detected) {
        res = 0.;
        return;
    }
    double dir_degree = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_EULER).x();
    res = (
        (0 <= dir_degree && dir_degree <= 180)
        ? dir_degree
        : dir_degree - 360
    ) * -PI / 180;
}

bool _BNO055::detected()
{
    return _detected;
}

double _BNO055::update_gyro_dir()
{
    static bool initialized = false;
    static uint64_t last_ms;

    uint64_t now_ms = millis();
    if (!initialized) {
        last_ms = now_ms;
        _last_gyro_dir = 0.0;
        return _last_gyro_dir;
    }
    uint64_t diff_ms = now_ms - last_ms;
    last_ms = now_ms;
    double gyro = Adafruit_BNO055::getVector(Adafruit_BNO055::VECTOR_GYROSCOPE).x();
    _last_gyro_dir += gyro * diff_ms / 1000;
    return _last_gyro_dir;
}

//! シングルトンオブジェクトへの参照
_BNO055 &_bno055 = _BNO055::instance();

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_BNO055_H */