#include <vector>
#include <algorithm>


std::vector<int> get_digit_vec(long int num, bool reversed = false) {
    /*
     * Return the digits of an integer in a vector<int>
     */
    std::vector<int> digit_vec;
    while (num) {
        digit_vec.push_back(num % 10);
        num /= 10;
    }
    if (!reversed)
        reverse(digit_vec.begin(), digit_vec.end());

    return(digit_vec);
}
