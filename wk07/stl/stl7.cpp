#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    if (v.size() > 0) {
        if (v.size() % 2 == 0) {
            sort(v.begin(), v.end());
            return (v[v.size() / 2] + v[(v.size() / 2) - 1]) / 2;
        } else {
            int n = v.size() / 2;
            nth_element(v.begin(), v.begin() + n, v.end());
            return v[n];
        }
    } else {
        return NOT_FOUND;
    }
}

