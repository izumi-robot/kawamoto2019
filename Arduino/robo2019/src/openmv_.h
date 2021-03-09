/**
 * @file openmv_.h
 * @brief I2C通信の読み取り用のクラス定義
 */

#pragma once

#ifdef ARDUINO

#include <Wire.h>

/**
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

/**
 * @brief I2C通信の読み取り用のクラス
 */
class I2CReader
{
private:
    //! 通信に使うワイヤオブジェクト
    TwoWire &_wire;
public:
    I2CReader() : _wire(Wire) {}
    /** @brief ワイヤオブジェクトを指定して初期化 */
    I2CReader(TwoWire &wire) : _wire(wire) {}

    /**
     * @fn static void setup()
     * @brief I2C通信が行えるようにセットアップする
     */
    static void setup();

    /**
     * @fn uint16_t pass_data()
     * @brief Wireストリームに溜まっているデータを破棄する
     * @return 破棄したデータのサイズ(byte)
     */
    static uint16_t pass_data();

    uint16_t read_2byte(uint8_t addr);

    /**
     * @fn uint16_t read_data_size(uint8_t addr)
     * @brief データサイズを取得する
     * @param[in] addr スレーブのアドレス
     * @return データのサイズ(byte)
     * @details リクエストに失敗した場合は0。`Wire.read()`は行われない。
     */
    uint16_t read_data_size(uint8_t addr);

    /**
     * @fn bool read_data(char *buff, uint8_t addr, uint16_t data_size)
     * @brief データを読む
     * @param[out] buff 読み取ったデータの保存先
     * @param[in]  addr スレーブのアドレス
     * @param[in]  data_size 読み取るデータのサイズ
     * @return 読み取りに成功したかどうか
     * @details 以下の場合には読み取り失敗となる。
     *          - buff == NULL
     *          - 取得可能なデータのサイズがdata_sizeより小さい
     *          読み取り失敗となった場合、`Wire.read()`は行われない。
     *          buffのサイズを確認せずに書き込むため、バッファオーバーランを起こす可能性がある。
     */
    bool read_data(char * buff, uint8_t addr, uint16_t data_size);

    /**
     * @fn bool read_data(uint8_t *buff, uint8_t addr, uint16_t data_size)
     * @brief データを読む
     * @param[out] buff 読み取ったデータの保存先
     * @param[in]  addr スレーブのアドレス
     * @param[in]  data_size 読み取るデータのサイズ
     * @return 読み取りに成功したかどうか
     * @sa bool read_data(char *buff, uint8_t addr, uint16_t data_size)
     */
    bool read_data(uint8_t * buff, uint8_t addr, uint16_t data_size);
};

/**
 * @class I2CReaderWithAddr
 * @brief アドレスを保存するI2CReader
 */
class I2CReaderWithAddr : public I2CReader
{
public:
    //! 保存するアドレス
    const uint8_t address;

    /**
     * @brief コンストラクター
     * @param addr 保存するアドレス
     */
    I2CReaderWithAddr(uint8_t addr) : I2CReader(), address(addr) {}

    /**
     * @fn uint16_t read_data_size()
     * @brief データサイズを取得する
     * @return データのサイズ(byte)
     * @details リクエストに失敗した場合は0。`Wire.read()`は行われない。
     */
    inline uint16_t read_data_size();

    /**
     * @fn bool read_data(char *buff, uint16_t data_size)
     * @brief データを読む
     * @param[out] buff 読み取ったデータの保存先
     * @param[in]  data_size 読み取るデータのサイズ
     * @return 読み取りに成功したかどうか
     * @details
     *  以下の場合には読み取り失敗となる。
     *  - buff == NULL
     *  - 取得可能なデータのサイズがdata_sizeより小さい
     *  読み取り失敗となった場合、`Wire.read()`は行われない。
     *  buffのサイズを確認せずに書き込むため、バッファオーバーランを起こす可能性がある。
     */
    inline bool read_data(char *, uint16_t);

    /**
     * @fn bool read_data(uint8_t *buff, uint16_t data_size)
     * @sa bool read_data(char *buff, uint16_t data_size)
     */
    inline bool read_data(uint8_t *, uint16_t);
};

class OpenMV {
private:
    TwoWire &_wire;
public:
    const uint8_t address;

    OpenMV() : _wire(Wire), address(0x12) {}
    OpenMV(uint8_t addr) : _wire(Wire), address(addr) {}
    OpenMV(TwoWire wire, uint8_t addr) : _wire(wire), address(adddr) {}

    void begin() { _wire.begin(); }

    uint16_t read_2byte() {
        return _wire.read() | (uint16_t(_wire.read()) << 8);
    }

    uint16_t read_data_size() {
        _wire.requestFrom(address, 2);
        if (_wire.available() == 2) {
            return read_2byte();
        }
        return 0;
    }

    CameraPos read_pos(
        const CameraPos &pos_on_fail = CameraPos{0, 0},
        uint16_t default_value = 0xffff
    ) {
        uint16_t data_size = read_data_size();
        _wire.requestFrom(address, data_size);
        if (_wire.available() != 4) return pos_on_fail;
        uint16_t x = read_2byte();
        uint16_t y = read_2byte();
        return (
            (x != default_value || y != default_value)
            ? CameraPos{x, y}
            : pos_on_fail
        );
    }
};

} // namespace robo

void robo::I2CReader::setup() { _wire.begin(); }

uint16_t robo::I2CReader::pass_data()
{
    uint16_t data_size = _wire.available();
    for (int i = 0; i < data_size; ++i) { _wire.read(); }
    return data_size;
}

uint16_t robo::I2CReader::read_data_size(uint8_t addr)
{
    _wire.requestFrom(addr, (uint8_t)2);
    if (_wire.available() == 2) {
        return _wire.read() | (_wire.read() << 8);
    }
    return 0;
}

bool robo::I2CReader::read_data(char *buff, uint8_t addr, uint16_t data_size)
{
    if (buff == NULL) return false;

    Wire.requestFrom(addr, data_size);
    if (Wire.available() < data_size) return false;

    for (uint16_t i = 0; i < data_size; ++i) {
        buff[i] = Wire.read();
    }
    return true;
}

bool robo::I2CReader::read_data(uint8_t *buff, uint8_t addr, uint16_t data_size)
{
    if (buff == NULL) return false;

    Wire.requestFrom(addr, data_size);
    if (Wire.available() < data_size) return false;

    for (uint16_t i = 0; i < data_size; ++i) {
        buff[i] = Wire.read();
    }
    return true;
}

uint16_t robo::I2CReaderWithAddr::read_data_size()
{
    return I2CReader::read_data_size(address);
}

bool robo::I2CReaderWithAddr::read_data(char *buff, uint16_t data_size)
{
    return I2CReader::read_data(buff, address, data_size);
}

bool robo::I2CReaderWithAddr::read_data(uint8_t *buff, uint16_t data_size)
{
    return I2CReader::read_data(buff, address, data_size);
}

#else /* ARDUINO */

#error This liblary is for Arduino.

#endif /* ARDUINO */