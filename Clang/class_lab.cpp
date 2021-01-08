#include <iostream>
#include <string>

using std::string;


class A
{
private:
    static int i;

    A() {}
    A(const A&) {}
    ~A() {}
    A& operator=(const A&) { return instance(); }

public:

    static A& instance()
    {
        static A ins;
        return ins;
    }

    struct {
        int geti() {
            return i;
        }
    } b;
};

int A::i = 0;

int main() {
    A *a = &A::instance();
    std::cout
        << a->b.geti() << "\n";
}