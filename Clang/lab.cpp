#include <iostream>
#include <string>

class A {
    public:
    int a;
    private:
    static class B {
        public:
        void seta(int _a) {
            a = _a;
        }
    };
    
};
