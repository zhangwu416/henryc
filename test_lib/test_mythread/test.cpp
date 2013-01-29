#include <iostream>
using namespace std;

#include "thread.h"

using namespace henrylib::mythread;

int main()
{
    cout << current_thread_t::tid() << "/" << current_thread_t::is_main_thread() << endl;
    thread_t t;
    t.start();
    t.stop();
    t.join();
    return 0;
}
