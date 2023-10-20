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
int sortMod3(std::vector<int>& v)
{
    try {
        std::partition(v.begin(), v.end(), [](int i) { return (i % 3) == 0; });
        std::partition(v.begin(), v.end(), [](int i) { return (i % 3) == 1; });

        std::sort(v.begin(), v.begin() + std::count_if(v.begin(), v.end(), [](int i) { return (i % 3) == 0; }));
        std::sort(v.begin() + std::count_if(v.begin(), v.end(), [](int i) { return (i % 3) == 0; }),
                  v.begin() + std::count_if(v.begin(), v.end(), [](int i) { return (i % 3) == 1; }));
        std::sort(v.begin() + std::count_if(v.begin(), v.end(), [](int i) { return (i % 3) == 1; }), v.end());

        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        return EXIT_FAILURE;
    }
}

