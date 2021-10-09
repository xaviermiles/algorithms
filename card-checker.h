#include <vector>
#include <algorithm>

bool luhn_algorithm(long int num) {
    /*
     * https://en.wikipedia.org/wiki/Luhn_algorithm
     * Used to check whether card number was mistyped (along with other uses).
     * Relatively simple check - "it will detect any single-digit error, as well
     * as well as almost all transpositions of adjacent digits."
     */
    auto num_copy = num / 10;
    std::vector<int> check_num_dgts;
    while (num_copy) {
        check_num_dgts.push_back(num_copy % 10);
        num_copy /= 10;
    }
    reverse(check_num_dgts.begin(), check_num_dgts.end());

    int double_dgt;
    for (std::vector<int>::iterator it = check_num_dgts.end() - 1;
         it >= check_num_dgts.begin(); ) {
        double_dgt = *it * 2;
        *it = 0;
        while (double_dgt) {
            *it += (double_dgt % 10);
            double_dgt /= 10;
        }
        it = it - 2;
    }

    int sum_transformed_dgts = 0;
    for (int &x : check_num_dgts)
        sum_transformed_dgts += x;

    int luhn_num = 10 - sum_transformed_dgts % 10;
    int check_digit = num % 10;  // final digit in original number
    bool check_digit_correct = check_digit == luhn_num;

    return check_digit_correct;
}
