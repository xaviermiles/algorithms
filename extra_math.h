#pragma once

#include"utils.h"

#include <math.h>
#include <vector>
#include <algorithm>

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

bool is_palindrome(int x) {
  /*
   * Is the integer a palindrome?
   */
  std::vector<int> digits;
  while (x > 0) {
    int final_digit = x % 10;
    digits.push_back(final_digit);
    x /= 10;
  }
  for (int i = 0; i < digits.size() / 2; i++) {
    if (digits[i] != digits[digits.size() - 1 - i])
      return false;
  }
  return true;
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

#include <iostream> // FOR DEBUGGING
vector<int> sieve_of_atkins(unsigned int n) {
  /*
   * NOT WORKING YET
   *
   * "modern algorithm" for finding prime numbers (created in 2003). This does
   * some more work at the start and achieves a better asymptotic complexity.
   * https://en.wikipedia.org/wiki/Sieve_of_Atkin
   */
  vector<int> results{2, 3, 5};
  vector<bool> is_prime(n, true);  // (i-1) slot refers to whether i is prime
  int r;
  vector<int> special_1{1, 13, 17, 29, 37, 41, 49, 53},
              special_2{7, 19, 31, 43},
              special_3{11, 23, 47, 59};
  // 3. Do the work at the start
  for (int z = 1; z < n; z++) {

    std::cout << z << std::endl;
    r = z % 60;
    if (std::any_of(special_1.cbegin(), special_1.cend(), [r](int x) { return r == x; })) {
      // 4x^2 + y^2 = z
      // <=> y = +/- sqrt(z - 4x^2)
      // only need positive square root, as primes must be positive
      std::cout << "special_1" << std::endl;
      for (int x = 1; x < n; x++) {
        // std::cout << x << '*' << sqrt(z - 4 * pow(x, 2.0)) << std::endl;
        double y = sqrt(z - 4 * pow(x, 2.0));
        if (isnan(y)) {
          break;
        } else if (floor(y) == y) {
          is_prime[x - 1] = !is_prime[x - 1];
          is_prime[y - 1] = !is_prime[y - 1];
        }
      }
    // } else if (true) {
    //   std::cout << "ooo" <<std::endl;
    } else if (std::any_of(special_2.cbegin(), special_2.cend(), [r](int x) { return r == x; })) {
      // 3x^2 + y^2 = i <=> y = +sqrt(z - 3x^2)
      std::cout << "special_2" << std::endl;
      for (int x = 1; x < n; x++) {
        double y = sqrt(z - 3 * pow(x, 2.0));
        if (isnan(y)) {
          break;
        } else if (floor(y) == y) {
          is_prime[x - 1] = !is_prime[x - 1];
          is_prime[y - 1] = !is_prime[y - 1];
        }
      }
    } else if (std::any_of(special_3.cbegin(), special_3.cend(), [r](int x) { return r == x; })) {
      // 3x^2 - y^2 = z; x > y <=> y = +sqrt(3x^2 - z); x > y
      std::cout << "special_3" << std::endl;
      for (int x = n; x > 0; x--) {
        double y = sqrt(3 * pow(x, 2.0) - z);
        if (isnan(y) || x < y) {
          break;
        } else if (floor(y) == y) {
          is_prime[x - 1] = !is_prime[x - 1];
          is_prime[y - 1] = !is_prime[y - 1];
        }
      }
    }
    for (auto i = 0;i < is_prime.size();i++) { std::cout << is_prime[i]; }
    std::cout << std::endl;
  }
  for (int i = 2; i < n; i++) {
    if (is_prime[i - 1]) {
      results.push_back(i);
      // Mark off multiples of this prime
      int square_mult = pow(i, 2.0);
      while (square_mult < n) {
        is_prime[square_mult - 1] = false;
        square_mult += pow(i, 2.0);
      }
    }
  }

  return results;
}
