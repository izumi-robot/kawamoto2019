/**
 * @file util.h
 * @brief ユーティリティ
 */

#ifndef ROBO2019_UTIL_H
#define ROBO2019_UTIL_H

#ifdef ARDUINO

/**
 * @namespace robo
 * @brief 自作ライブラリの機能をまとめたもの
 */
namespace robo
{

/**
 * @brief センサー類の基底クラス
 */
class Sensor
{
public:
    /**
     * @fn void setup();
     * @brief モーターのセットアップを行う
     * @note 全体のsetup内で呼ばないと他の機能が使えない。
     */
    virtual void setup() = 0;
    /**
     * @fn unsigned int read()
     * @brief センサーの値を読む
     * @return 読んだ値
     */
    virtual int read() = 0;
};

/**
 * @class SingletonBase
 * @brief シングルトンのテンプレートクラス
 * @tparam Derived 派生のシングルトンクラス
 * @details https://qiita.com/_meki/items/96acf0b45c75c17d6dec
 * @note
        シングルトンクラスFooを作る例:
        class Foo : SingletonBase<Foo> { ... };
 */
template<class Derived> class SingletonBase
{
protected:
    SingletonBase() = default;
    ~SingletonBase() = default;

    SingletonBase(const SingletonBase &) = delete;
    SingletonBase& operator=(const SingletonBase &) = delete;

public:
    /**
     * @fn Derived& instance()
     * @brief シングルトンのインスタンス取得用
     * @return インスタンスの参照
     */
    static Derived& instance();
};

template<class Derived> Derived& SingletonBase<Derived>::instance()
{
    static Derived ins;
    return ins;
}

/**
 * @namespace string
 * @brief 文字列操作用の関数群
 */
namespace string {
    /**
     * @fn String rjust(const String &target, uint8_t width, char padding)
     * @brief widthの長さをもつ右寄せした文字列を返す。左側にpaddingの文字を埋める。
     * @param[in] target 右寄せする文字列
     * @param[in] width 右寄せした後の長さ
     * @param[in] padding 左に埋める文字
     * @return 右寄せ後の文字列
     */
    String rjust(const String &, uint8_t, char);

    /**
     * @fn void rjust(String *dst, const String &target, uint8_t width, char padding)
     * @brief widthの長さをもつ右寄せした文字列を返す。左側にpaddingの文字を埋める。
     * @param[in] target 右寄せする文字列
     * @param[in] width 右寄せした後の長さ
     * @param[in] padding 左に埋める文字
     * @param[out] dst 右寄せ後の文字列
     */
    void rjust(String *, const String &target, uint8_t, char);

    /**
     * @fn void rjust(String *target, uint8_t width, char padding)
     * @brief widthの長さをもつ右寄せした文字列を返す。左側にpaddingの文字を埋める。
     * @param[in]  target 右寄せする文字列
     * @param[out] target 右寄せ後の文字列
     * @param[in] width 右寄せした後の長さ
     * @param[in] padding 左に埋める文字
     */
    void rjust(String *target, uint8_t, const char &);
} // namespace string

String string::rjust(const String &target, uint8_t width, char padding)
{
    String rjusted_str = target;
    for (uint8_t i = rjusted_str.length(); i < width; ++i) {
        rjusted_str = padding + rjusted_str;
    }
    return rjusted_str;
}

void string::rjust(String *dst, const String &target, uint8_t width, char padding)
{
    *dst = target;
    for (uint8_t i = target.length(); i < width; ++i)
    {
        *dst = padding + (*dst);
    }
}

void string::rjust(String *target, uint8_t width, const char &padding)
{
    for (uint8_t i = target->length(); i < width; ++i)
    {
        *target = padding + (*target);
    }
}

} // namespace robo

#else /* ARDUINO */

static_assert(0, "This liblary is for Arduino.");

#endif /* ARDUINO */

#endif /* ROBO2019_UTIL_H */