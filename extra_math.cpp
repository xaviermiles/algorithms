#include "extra_math.h"
#include "utils.h"

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
  for (auto & set: test_sets) {
    // Checks symmetry
    cout << (euclids_gcd(set[0], set[1]) == set[2]) << ", " <<
            (euclids_gcd(set[1], set[0]) == set[2]) << endl;
  }
  cout << endl;
}

void test_factorial() {
  int test_sets[4][2] = {
    {0, 1},
    {1, 1},
    {3, 6},
    {5, 120}
  };
  cout << "Testing factorial" << '\n';
  for (auto &set : test_sets) {
    cout << (factorial(set[0]) == set[1]) << ", ";
  }
  cout << "\n\n";
}

void test_is_coprime() {
  int test_sets[2][3] = {
    {14, 25, 1},
    {14, 21, 0}
  };
  cout << "Testing is_coprime" << endl;
  for (auto &set: test_sets) {
    cout << (is_coprime(set[0], set[1]) == set[2]) << ", " <<
            (is_coprime(set[1], set[0]) == set[2]) << endl;
  }
  cout << endl;
}

void test_lcm() {
  int test_sets[2][3] = {
    {4, 10, 20},
    {-5, 12, -60}
  };
  cout << "Testing lcm" << endl;
  for (auto &set: test_sets) {
    cout << (lcm(set[0], set[1]) == set[2]) << ", " <<
            (lcm(set[1], set[0]) == set[2]) << endl;
  }
  cout << endl;
}

void test_is_prime() {
  // TODO: add bigger primes?
  unsigned int test_sets[2][3] = {
    {7919, 1},
    {7918, 0}
  };
  cout << "Testing is_prime" << endl;
  for (auto & set: test_sets) {
    cout << (is_prime(set[0]) == set[1]) << endl;
  }
  cout << endl;
  }

void test_sieve_of_eratosthenes() {
  cout << "Testing sieve_of_eratosthenes and segmented_sieve_of_eratosthenes"
       << endl;
  int n = 30;
  std::vector<int> expected = {2,3,5,7,11,13,17,19,23,29};
  cout << (sieve_of_eratosthenes(n) == expected ? "ya" : "na") << '\n' <<
          (segmented_sieve_of_eratosthenes(n, 0.5) == expected ? "ya" : "na") <<
          (segmented_sieve_of_eratosthenes(n, 0.9) == expected ? "ya" : "na") <<
          (segmented_sieve_of_eratosthenes(n, 0.2) == expected ? "ya" : "na") <<
          endl;
  std::string sep = ", ";
  cout << join_vec(segmented_sieve_of_eratosthenes(n, 0.5), sep) << endl;
  cout << join_vec(sieve_of_atkins(n), sep) << endl;
}

int main() {
  test_euclids_gcd();
  test_factorial();
  test_is_coprime();
  test_lcm();

  test_is_prime();
  test_sieve_of_eratosthenes();
}
