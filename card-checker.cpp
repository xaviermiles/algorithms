#include "card-checker.h"

#include <iostream>

void test_luhn_algorithm()
{
    long int test_nums[2] = {
        79927398713, // should pass
        123456789    // should not pass
    };
    for (auto &i : test_nums) {
        bool passes_test = luhn_algorithm(i);
        std::cout << i << " - " << (passes_test ? "Yay" : "Nay") << std::endl;
    }
}

void test_verhoeff_algorithm()
{
    long int test_nums[2] = {
        2363,     // should pass
        123456789 // shouldn't pass
    };
    for (auto &x : test_nums) {
        bool passes_test = verhoeff_algorithm(x);
        std::cout << x << " - " << (passes_test ? "Yay" : "Nay") << std::endl;
    }
}

int main()
{
    // Uncomment as wanted:
    // test_luhn_algorithm();
    // test_verhoeff_algorithm();
}
