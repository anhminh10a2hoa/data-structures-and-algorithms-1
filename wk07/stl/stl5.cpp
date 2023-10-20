#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
bool divthree(int i) {
    return (i % 3) == 0;
}
bool divisone(int i) {
    return (i % 3) == 1;
}

int sortMod3(std::vector < int > & v) {
    try {
        auto split = partition(v.begin(), v.end(), divthree);
        auto delimit = partition(split, v.end(), divisone);
        sort(v.begin(), split);
        sort(split, delimit);
        sort(delimit, v.end());
        return EXIT_SUCCESS;
    } catch (const std::exception & e) {
        return EXIT_FAILURE;
    }
}