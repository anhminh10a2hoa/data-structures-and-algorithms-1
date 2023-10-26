#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>
#include <variant>

#include "CLI11.hpp"
#include "test.hh"

using namespace std;

int getRandom(int upper)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, upper);
    return dis(gen);
}

std::vector<int> getRandomVector(int size)
{
    std::vector<int> v;

    for (int i = 0; i < size; i++) {
        v.push_back(getRandom(size * 4));
    }

    return v;
}

std::vector<int> getSequence(int size)
{
    std::vector<int> v(size);

    const int rnd = getRandom(size);

    for (int x = 0; x < size; ++x) {
        v[x] = rnd + x;
    }

    return v;
}

std::map<string, int> getMap(const std::vector<int>& v)
{
    std::map<string, int> m;
    for (std::size_t i = 0; i < v.size(); i++) {
        m.insert( std::pair<string, int>("val" + std::to_string(i) , v[i]) );
    }
    return m;
}

void printVector(const std::vector<int>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
    cout << endl << endl;
}

void printMap(const std::map<string, int>& m)
{
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << "{" << it->first << " : " << it->second << "} ";
    }
    cout << endl << endl;
}

void test(int func_id, int size, int search_val)
{
    std::vector<int> v = getRandomVector(size);

    switch (func_id)
    {
    case 1:
    {
        cout << "Testing function sortAsc() with the following data:" << endl << endl;
        printVector(v);

        if (EXIT_FAILURE == sortAsc(v)) {
            cout << "Your function failed and returned EXIT_FAILURE" << endl;
        } else {
            cout << "The vector after sortAsc():" << endl << endl;
            printVector(v);
        }
        break;
    }
    case 2:
    {
        cout << "Testing function sortDesc() with the following data:" << endl << endl;
        printVector(v);

        if (EXIT_FAILURE == sortDesc(v)) {
            cout << "Your function failed and returned EXIT_FAILURE" << endl;
        } else {
            cout << "The vector after sortDesc():" << endl << endl;
            printVector(v);
        }
        break;
    }
    case 3:
    {
        cout << "Testing function findGivenValue() with the following data:" << endl << endl;
        printVector(v);

        auto iter = findGivenValue(v, search_val);
        cout << "Searched for " << search_val;

        if (iter != v.end()) {
            if (*iter == search_val) {
                cout << " and found it at index " << std::distance(v.begin(), iter) << "." << endl;
            } else {
                cout << " but the returned iterator refers to " << *iter << " instead." << endl;
            }
        } else {
            cout << " but couldn't find it." << endl;
        }
        break;
    }
    case 4:
    {
        cout << "Testing function findLastEven() with the following data:" << endl << endl;
        printVector(v);

        auto iter = findLastEven(v);
        cout << "Searched for last even value";

        if (iter != v.rend()) {
            cout << " and found " << *iter << " at index " << v.size() - std::distance(v.rbegin(), iter) - 1 << "." << endl;
        } else {
            cout << " but couldn't find any even values." << endl;
        }
        break;
    }
    case 5:
    {
        cout << "Testing function sortMod3() with the following data:" << endl << endl;
        printVector(v);

        if (EXIT_FAILURE == sortMod3(v)) {
            cout << "Your function failed and returned EXIT_FAILURE" << endl;
        } else {
            cout << "The vector after sortMod3():" << endl << endl;
            printVector(v);
        }
        break;
    }
    case 6:
    {
        map<string, int> m = getMap(v);
        cout << "Testing function findAtLeastGiven() with the following data:" << endl << endl;
        printMap(m);

        int found = findAtLeastGiven(m, search_val);
        cout << "Searched for value at least " << search_val;

        if (found != NOT_FOUND) {
            if (found >= search_val) {
                cout << " and found " << found << endl;
            } else {
                cout << " but function returned " << found << " instead." << endl;
            }
        } else {
            cout << " but couldn't find it." << endl;
        }
        break;
    }
    case 7:
    {
        cout << "Testing function findMedian() with the following data:" << endl << endl;
        printVector(v);

        int median = findMedian(v);
        cout << "Searched for median";

        if (median != NOT_FOUND) {
            cout << " and your function returned " << median << endl;
        } else {
            if (v.size() > 0) {
                cout << " but your function erroneously returned NOT_FOUND" << endl;
            } else {
                cout << " but the vector was empty and your function returned correctly NOT_FOUND." << endl;
            }
        }
        break;
    }
    case 8:
    {
        cout << "Testing function removeLessThan() with the following data:" << endl << endl;
        printVector(v);

        cout << "Tried to remove all elements less than " << search_val << endl;
        if (EXIT_FAILURE == removeLessThan(v, search_val)) {
            cout << "Your function failed and returned EXIT_FAILURE" << endl;
        } else {
            cout << "The vector after removeLessThan():" << endl << endl;
            printVector(v);
        }
        break;
    }
    default:
        break;
    }
}

const int NUMBER_OF_FUNCTIONS = 8;

int main(int argc, char *argv[])
{
    int selected_function = -1;
    int number_of_items = -1;
    int search_value = -1;
    std::vector<int> data = {};
    CLI::App app{"Week 07 stl"};
    app.add_option("test_function", selected_function, "1|2|3|4|5|6|7|8 (number of the function to test as in stl1.cc, stl2.cc, ...)")->required();
    app.add_option("num_of_items", number_of_items,"number of items in the test vector (optional, default=10)")->default_val(10);
    app.add_option("search_value",search_value,"number to search or limit results (the second parameter to the function when needed, default=25)")->default_val(25);

    try {
        app.parse(argc,argv);
    } catch (const CLI::ParseError & e) {
        cout << app.help();
        app.exit(e);
        return EXIT_FAILURE;
    }
    using namespace std;
    if (selected_function<1 || selected_function > NUMBER_OF_FUNCTIONS) {
        cout << "No such test function" << endl;
        return EXIT_FAILURE;
    }
    if (number_of_items < 1) {
        cout << "num_of_items should be a positive integer larger than 0"<<endl;
        return EXIT_FAILURE;
    }


    test(selected_function, number_of_items, search_value);
    return EXIT_SUCCESS;
}
