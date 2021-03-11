#include <iostream>
#include <type_traits>

template<typename T>
struct Foo {
    T val;
    template<typename _ = void>
    void f();
};

template<typename T>
void Foo<T>::f< std::enable_if_t<std::is_floating_point<T>::value, void>>() {
    std::cout << "floating point: " << val << std::endl;
}

template<typename T>
void Foo<T>::f<std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value, void>>() {
    std::cout << "unsigned integral: " << val << std::endl;
}

template<typename T>
void Foo<T>::f<std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value, void>>() {
    std::cout << "signed integral: " << val << std::endl;
}

int main() {
    Foo f1{0.1};
    Foo f2{1};
    Foo f3{3u};
    f1.f(); f2.f(); f3.f();
}