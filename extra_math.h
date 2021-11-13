#pragma once

#include <math.h>
#include <vector>

using std::vector;

int euclids_gcd(int x, int y) {
    /*
     * Returns the greatest common divisor of two integers
     *
     * https://en.wikipedia.org/wiki/Algorithm#Euclid's_algorithm
     */
    int r;
    if (x == 0 | y == 0) return 0;

    if (y > x) { // swap so x is biggest
        r = x;
        x = y;
        y = r;
    }

    while (true) {
        r = x % y;
        if (r == 0) return abs(y);
        x = y;
        y = r;
    }
}

bool is_coprime(int x, int y) {
    /*
     * Is the two integers coprime/relatively prime?
     */
    return euclids_gcd(x, y) == 1;
}

int lcm(int x, int y) {
    /*
     * Least common multiple of two integers
     */
    return x * y / euclids_gcd(x, y);
}

bool is_prime(unsigned int n) {
    /*
     * Is the integer a prime number? - Trial division technique
     */
    for (int x = 2; x <= ceil(sqrt(n)); x++) {
        if (euclids_gcd(n, x) > 1) return false;
    }
    return true;
}

vector<int> sieve_of_eratostheses(unsigned int n) {
    /*
     * Return a vector of prime numbers up to non-negative number `n`
     */
    vector<bool> is_idx_prime(n - 1, true);  // don't need slot for 1
    for (int i = 2; i <= ceil(sqrt(n)); i++) {
        if (is_idx_prime[i - 2]) {
            // mark off all multiples (starting from square) as false
            for (int j = i * i; j <= n;) {
                is_idx_prime[j - 2] = false;
                j = j + i;
            }
        }
    }
    // the indices-minus-two of `is_idx_prime` which map to true are prime
    vector<int> prime_nums;
    for (auto i = 2; i <= n; i++) {
        if (is_idx_prime[i - 2]) prime_nums.push_back(i);
    }
    return prime_nums;
}
