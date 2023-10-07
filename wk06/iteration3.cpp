/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    // ADD YOUR CODE HERE
    int size = lst.size();
    int count = 0;

    for (const int& item : lst) {
        std::cout << item << ' ';
        ++count;

        if (count == size / 2) {
            break;
        }
    }

    std::cout << std::endl;
}
