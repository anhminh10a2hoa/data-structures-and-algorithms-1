#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief creates a vector with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 */
std::vector<int> ascendingVector(int n) {
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) { v.push_back(i); }

    return v;
}

