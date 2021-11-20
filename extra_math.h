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

vector<int> sieve_of_eratosthenes(unsigned int n) {
    /*
     * Return a vector of prime numbers up to non-negative number `n`
     */
    vector<bool> is_idx_prime(n - 1, true);  // don't need slot for 1
    for (int i = 2; i <= ceil(sqrt(n)); i++) {
        if (is_idx_prime[i - 2]) {
            // mark off all multiples (starting from square) as false
            for (int j = i * i; j <= n;) {
                is_idx_prime[j - 2] = false;
                j += i;
            }
        }
    }
    // the indices-minus-two of `is_idx_prime` which map to true are prime
    vector<int> primes;
    for (auto i = 2; i <= n; i++) {
        if (is_idx_prime[i - 2]) {
            primes.push_back(i);
        }
    }
    return primes;
}

vector<int> segmented_sieve_of_eratosthenes(unsigned int n, float d) {
    /*
     * Less memory-intensive version of `sieve_of_eratosthenes()`
     * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve
     *
     * `d` is the segment size as a proportion of sqrt(n) - must be in (0, 1]
     * NB: this does not check prime-ness of 0 and 1
     */
    vector<int> primes;
    if (d > 1) {
        d = 1;
    } else if (d < 0.1) {
        d = 0.1;
    }

    // 1. Divide 2..n into segments of size d (or <=d for final segment)
    size_t bin_size = round(d * sqrt(n));
    size_t num_bins = ceil((n - 2) / bin_size);
    int idx_bound, bins[num_bins][bin_size];
    // the last bin may have some unused spots:
    std::fill_n(bins[num_bins], bin_size, -1);
    for (int i = 0; i <= num_bins; i++) {
        // How to efficiently omit numbers greater than n?
        if (i == num_bins) {
            idx_bound =  (n - 2) - (num_bins * bin_size);
        } else {
            idx_bound = bin_size;
        }
        for (int j = 0; j <= idx_bound; j++) {
            bins[i][j] = i * bin_size + j + 2;
        }
    }

    // 2. Find the primes in the first/lowest segment using regular sieve
    primes = sieve_of_eratosthenes(bins[0][bin_size - 1]);

    // 3.
    vector<int> is_prime_per_bin(bin_size);
    int high;  // max number for each bin
    for (int i = 1; i <= num_bins; i++) {
        for (auto &x : is_prime_per_bin) x = true;  // reset
        if (i == num_bins) {
            idx_bound = (n - 2) - (num_bins * bin_size);
            high = n;
        } else {
            idx_bound = bin_size;
            high = bins[i][bin_size];
        }

        for (auto j = 0; j < primes.size() & primes[j] <= sqrt(high); j++) {
            // ...find lowest multiple of p between m-d and m, and enumerating
            // its multiples in steps of p as usual.
            for (int k = primes[j]; k <= high; k += primes[j]) {
                if (k >= bins[i][0]) {
                    is_prime_per_bin[k - bins[i][0]] = false;
                }
            }
        }
        // push results into `primes`
        for (int z = 0; z <= idx_bound; z++) {
            if (is_prime_per_bin[z]) {
                primes.push_back(bins[i][z]);
            }
        }
    }
    return primes;
}
