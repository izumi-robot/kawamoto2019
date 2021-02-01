/**
 * @file i2c.h
 * @brief I2C通信の読み取り用のクラス定義
 */

#ifndef ROBO2019_I2C_H
#define ROBO2019_I2C_H

#ifdef ARDUINO

#include <Wire.h>

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

/**
 * @class I2CReader
 * @brief I2C通信の読み取り用のクラス
 */
class I2CReader
{
public:
    /**
     * @fn static void begin()
     * @brief I2C通信が行えるようにセットアップする
     */
    static void begin();

    /**
     * @fn uint16_t pass_data()
     * @brief Wireストリームに溜まっているデータを破棄する
     * @return 破棄したデータのサイズ(byte)
     */
    static uint16_t pass_data();

    /**
     * @fn uint16_t read_data_size(uint8_t addr)
     * @brief データサイズを取得する
     * @param[in] addr スレーブのアドレス
     * @return データのサイズ(byte)
     * @details リクエストに失敗した場合は0。`Wire.read()`は行われない。
     */
    uint16_t read_data_size(uint8_t);

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
    bool read_data(char *, uint8_t, uint16_t);

    /**
     * @fn bool read_data(uint8_t *buff, uint8_t addr, uint16_t data_size)
     * @brief データを読む
     * @param[out] buff 読み取ったデータの保存先
     * @param[in]  addr スレーブのアドレス
     * @param[in]  data_size 読み取るデータのサイズ
     * @return 読み取りに成功したかどうか
     * @sa bool read_data(char *buff, uint8_t addr, uint16_t data_size)
     */
    bool read_data(uint8_t *, uint8_t, uint16_t);
};

/**
 * @class I2CReaderWithAddr
 * @brief アドレスを保存するI2CReader
 */
class I2CReaderWithAddr : public I2CReader
{
public:
    using I2CReader::begin;
    using I2CReader::pass_data;

    const uint8_t address;
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
     * @details 以下の場合には読み取り失敗となる。
     *          - buff == NULL
     *          - 取得可能なデータのサイズがdata_sizeより小さい
     *          読み取り失敗となった場合、`Wire.read()`は行われない。
     *          buffのサイズを確認せずに書き込むため、バッファオーバーランを起こす可能性がある。
     */
    inline bool read_data(char *, uint16_t);

    /**
     * @fn bool read_data(uint8_t *buff, uint16_t data_size)
     * @sa bool read_data(char *buff, uint16_t data_size)
     */
    inline bool read_data(uint8_t *, uint16_t);
};

} // namespace robo


void robo::I2CReader::begin()
{
    Wire.begin();
}

uint16_t robo::I2CReader::pass_data()
{
    uint16_t data_size = Wire.available();
    for (int i = 0; i < data_size; ++i) {
        Wire.read();
    }
    return data_size;
}

uint16_t robo::I2CReader::read_data_size(uint8_t addr)
{
    Wire.requestFrom(addr, (uint8_t)2);
    if (Wire.available() == 2) {
        return Wire.read() | (Wire.read() << 8);
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

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_I2C_H */