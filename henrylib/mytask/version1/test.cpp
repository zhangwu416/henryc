#include "bind.h"
#include <iostream>
using namespace std;
using namespace henrylib::mybind;

class test
{
typedef void (test::*func_ptr)(int, int);
    public:
        void myprint()
        {
            cout << 2 << ":" << 3 << endl;
        }
        void print()
        {
            bind_t test = bind_t::bind_memfunc(this, &test::myprint);
            test();
        }
};

void print_int(int a)
{
    cout << "a:" << a << endl;
}


int main()
{
    bind_t test = bind_t::bind_func(&print_int, 2);
    test();
}
