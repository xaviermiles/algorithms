#include <vector>
#include <algorithm>

bool luhn_algorithm(long int num)
{
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

bool verhoeff_algorithm(long int num)
{
    /*
     * https://en.wikipedia.org/wiki/Verhoeff_algorithm
     * Checksum formula for error detection
     * "detects all single-digit errors and all transposition errors involving
     * two adjacent digits"
     *
     * Can be performed using three tables:
     * d: Cayley table of the dihedral group D_5
     * inv: multiplicative inverse of the index
     * p: specific permutation applied iteratively
     */
    int d[10][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 0, 6, 7, 8, 9, 5},
        {2, 3, 4, 0, 1, 7, 8, 9, 5, 6},
        {3, 4, 0, 1, 2, 8, 9, 5, 6, 7},
        {4, 0, 1, 2, 3, 9, 5, 6, 7, 8},
        {5, 9, 8, 7, 6, 0, 4, 3, 2, 1},
        {6, 5, 9, 8, 7, 1, 0, 4, 3, 2},
        {7, 6, 5, 9, 8, 2, 1, 0, 4, 3},
        {8, 7, 6, 5, 9, 3, 2, 1, 0, 4},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
    };
    int inv[10] = {0, 4, 3, 2, 1, 5, 6, 7, 8, 9};
    int p[8][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 5, 7, 6, 2, 8, 3, 0, 9, 4},
        {5, 8, 0, 3, 7, 9, 6, 1, 4, 2},
        {8, 9, 1, 6, 0, 4, 3, 5, 2, 7},
        {9, 4, 5, 3, 1, 2, 6, 8, 7, 0},
        {4, 2, 8, 6, 5, 7, 3, 9, 0, 1},
        {2, 7, 9, 3, 8, 0, 6, 4, 1, 5},
        {7, 0, 4, 6, 9, 1, 3, 2, 5, 8}
    };

    // Create array out of the individual digits of *num*, right to left
    std::vector<int> num_dgts;
    while (num) {
        num_dgts.push_back(num % 10);
        num /= 10;
    }
    // For each index i=1,2,...,len(num_dgts): c = d(c, p(i mod 8, num[i]))
    int c = 0;
    for (auto idx = 0; idx != num_dgts.size(); idx++) {
        c = d[c][p[num_dgts[idx] % 8][idx]];
    }
    // *num* is valid iff c=0
    bool check_dgt_correct = c == 0;

    return check_dgt_correct;
}
