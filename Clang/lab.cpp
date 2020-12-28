#include <iostream>
#include <vector>
#include <string>

using vint = std::vector<int>;
using std::string;

namespace N {

    class A {
        private:
        int x, y;
        public:
        A() : x(0), y(0) {}

        A(int x, int _y) {
            this->x = x;
            y = _y;
        }
        int f();
        int getx() {
            return x;
        }
        void setx(int val) {
            x = val >= 0 ? val : -val;
        }
    };

}

int N::A::f() {
    return x * y;
}


vint v1 = vint(3, 5);
vint v2{2, 4, 4};

string vector_to_string(const vint *vp) {
    string result = "[";
    for (auto it = vp->begin(); it != vp->end(); it++) {
        result += std::to_string(*it) + ", ";
    }
    auto end = result.end();
    result.erase(end - 2, end);
    return result + "]";
}

int main() {
    N::A a(2, 4);
    std::cout << a.f() << std::endl;
    std::cout << vector_to_string(&v2) << std::endl;
}
