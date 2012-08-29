#include <iostream>
using namespace std;


#include "placeholdes.h"
#include "bind.h"
using namespace henrylib::mybind;

void myprint()
{
    cout << "hello" << endl;
}


class test_t
{
    public:
        void print()
        {
            cout << "hello" << endl;
        }
        void print2()
        {
            cout << "hello" << endl;
        }
};

class test_t2
{
    public:
        void print()
        {
            cout << "hello" << endl;
        }
        void print2()
        {
            cout << "hello" << endl;
        }
};
int main()
{
    bind(&myprint)();
    test_t a, aa;
//    bind(&test_t::print, &a)();

    int b;
    cout << typeid(&test_t::print).name() << endl;
    cout << typeid(&test_t2::print2).name() << endl;
    cout << typeid(&a).name() << endl;
    cout << typeid(&aa).name() << endl;
    cout << typeid(b).name() << endl;
    return 0;
}
