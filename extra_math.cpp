#include "extra_math.h"

#include <iostream>

using std::cout;
using std::endl;

void test_euclids_gcd() {
    // array of {x, y, gcd}
    int test_sets[6][3] = {
        {49, 21, 7},
        {0, 2, 0},
        {1, 10, 1},
        {5, 7, 1},
        {-30, 20, 10},
        {-30, -20, 10}
    };
    cout << "Testing euclids_gcd" << endl;
    for (auto &set: test_sets) {
        // Checks symmetry
        cout << (euclids_gcd(set[0], set[1]) == set[2]) << ", " <<
                (euclids_gcd(set[1], set[0]) == set[2]) << endl;
    }
    cout << endl;
}

int main() {
    test_euclids_gcd();
}
