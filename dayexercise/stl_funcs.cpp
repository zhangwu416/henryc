#include <iostream>
using namespace std;

#include <set>
#include <vector>
#include <algorithm>

struct compare_t
{
    bool operator() (const std::pair<int, double>& pair1_, const std::pair<int, double>& pair2_)
    {
        return pair1_.first < pair2_.first;
    }
};

int main()
{
    //! first member compare first, and then second
    std::pair<int, double> test1(1, 2.0);
    std::pair<int, double> test2(2, 2.2);
    std::pair<int, double> test3(1, 2.3);
    std::pair<int, double> test4(1, 2.4);

    cout << (test1 < test2) << endl; // 1
    cout << (test2 < test3) << endl; // 0
    cout << (test3 < test4) << endl; // 1
    cout << (test3 < test1) << endl; // 0
    cout << endl;

    std::set<std::pair<int, double>, compare_t> elements;
    elements.insert(test1);
    elements.insert(test2);
    elements.insert(test3);
    elements.insert(test4);
    for (std::set<std::pair<int, double>, compare_t>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        cout << it->first << ":" << it->second << endl;
    }

    std::pair<int, double> test5(3, 2.4);
    std::set<std::pair<int, double>, compare_t>::iterator it = std::lower_bound(elements.begin(), elements.end(), test5, compare_t());
    //std::set<std::pair<int, double>, compare_t>::iterator it = elements.lower_bound(test5);
    if (it == elements.end())
    {
        cout << "not foud" << endl;
    }
    else
    {
        cout << it->first << ":" << it->second << endl;
    }
    
    std::vector<std::pair<int, double> > elements_test;
    std::copy(elements.begin(), it, std::back_inserter(elements_test));
    cout << endl << endl;
    for (std::vector<std::pair<int, double> >::iterator it = elements_test.begin(); it != elements_test.end(); ++it)
    {
        cout << it->first << ":" << it->second << endl;
    }

    //!拷贝到自己：
    std::copy(elements_test.begin(), elements_test.end(), std::back_inserter(elements_test));
    cout << endl << endl;
    for (std::vector<std::pair<int, double> >::iterator it = elements_test.begin(); it != elements_test.end(); ++it)
    {
        cout << it->first << ":" << it->second << endl;
    }
    return 0;
}
