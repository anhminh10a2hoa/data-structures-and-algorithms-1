#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    vector<int> result;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] % 2 == 0) {
            result.push_back(vec[i]);
            result.push_back(vec[i]);
        }
    }
    vec = result;
}

