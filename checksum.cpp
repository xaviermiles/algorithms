#include "checksum.h"

#include <iostream>

using std::cout;
using std::endl;

void test_luhn_algorithm()
{
    cout << "Testing Luhn" << endl;
    long int test_nums[2] = {
        79927398713, // should pass
        123456789    // should not pass
    };
    for (auto &x : test_nums) {
        bool passes_test = Luhn::validate_check_dgt(x);
        cout << x << " - " << (passes_test ? "Yay" : "Nay") << endl;
    }
    cout << endl;
}

void test_verhoeff_algorithm()
{
    cout << "Testing Verhoeff" << endl;
    long int test_nums[2] = {
        2363,     // should pass
        123456789 // shouldn't pass
    };
    for (auto &x : test_nums) {
        bool passes_test = Verhoeff::validate_check_dgt(x);
        cout << x << " - " << (passes_test ? "Yay" : "Nay") << endl;
    }
    cout << endl;
}

void test_damm_algorithm()
{
    cout << "Testing Damm" << endl;
    long int test_nums[2] = {
        5724,     // should pass
        123456789 // shouldn't pass
    };
    for (auto &x : test_nums) {
        bool passes_test = Damm::validate_check_dgt(x);
        cout << x << " - " << (passes_test ? "Yay" : "Nay") << endl;
    }
    cout << endl;
}

int main()
{
    // Uncomment as wanted:
    test_luhn_algorithm();
    test_verhoeff_algorithm();
    test_damm_algorithm();
}
