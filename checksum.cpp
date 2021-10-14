#include "checksum.h"

#include <iostream>

void test_luhn_algorithm()
{
    std::cout << "Testing Luhn" << std::endl;
    long int test_nums[2] = {
        79927398713, // should pass
        123456789    // should not pass
    };
    for (auto &x : test_nums) {
        Luhn luhn;
        bool passes_test = luhn.validate_check_dgt(x);
        std::cout << x << " - " << (passes_test ? "Yay" : "Nay") << std::endl;
    }
}

void test_verhoeff_algorithm()
{
    std::cout << "Testing Verhoeff" << std::endl;
    long int test_nums[2] = {
        2363,     // should pass
        123456789 // shouldn't pass
    };
    for (auto &x : test_nums) {
        Verhoeff verhoeff;
        bool passes_test = verhoeff.validate_check_dgt(x);
        std::cout << x << " - " << (passes_test ? "Yay" : "Nay") << std::endl;
    }
}

void test_damm_algorithm()
{
    std::cout << "Testing Damm" << std::endl;
    long int test_nums[2] = {
        5724,     // should pass
        123456789 // shouldn't pass
    };
    for (auto &x : test_nums) {
        Damm damm;
        bool passes_test = damm.validate_check_dgt(x);
        std::cout << x << " - " << (passes_test ? "Yay" : "Nay") << std::endl;
    }
}

int main()
{
    // Uncomment as wanted:
    // test_luhn_algorithm();
    // test_verhoeff_algorithm();
    // test_damm_algorithm();
}
