#include "util.h"

template<typename Derived> Derived& robo::SingletonBase<Derived>::instance()
{
    static Derived ins;
    return ins;
}