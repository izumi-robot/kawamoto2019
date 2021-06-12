/**
 * @file interrupt.ino
 * @brief Interruptクラスの使用例
 */

#include <robo2019.h>

// [テンプレートについて](https://qiita.com/hal1437/items/b6deb22a88c76eeaf90c)

// 2番ピンで割り込み
using I2 = robo::Interrupt<2, RISING>;

// 状態管理用のオブジェクト
I2 & i2 = I2::instance();

void setup()
{
    Serial.begin(9600);
    i2.setup();
}

void loop()
{
    if (i2.changed())
    {   // 割り込みが発生した
        char buff[128] = "";
        // 割り込みが発生する度にi2.state()のtrue/falseが切り替わる
        // 最初はfalseなので、割り込みが奇数回発生した場合はtrue
        sprintf_P(buff, PSTR("interrupt occured.\nstate: %s\n"), i2.state() ? PSTR("true") : PSTR("false"));
        Serial.print(buff);
    }
}
