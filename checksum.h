#pragma once

#include "utils.h"

#include <vector>

class AbstractChecksum {
public:
  int calculate_check_dgt(long int num);
  bool validate_check_dgt(long int num);
};

class Luhn: public AbstractChecksum {
  /*
   * https://en.wikipedia.org/wiki/Luhn_algorithm
   */

  public: static int calculate_check_dgt(long int num) {
    std::vector < int > num_dgts = get_digit_vec(num);

    int double_dgt;
    for (std::vector < int > ::iterator it = num_dgts.end() - 1; it >= num_dgts.begin();) {
      double_dgt = * it * 2;
      * it = 0;
      while (double_dgt) {
        * it += (double_dgt % 10);
        double_dgt /= 10;
      }
      it = it - 2;
    }

    int sum_transformed_dgts = 0;
    for (int & x: num_dgts)
      sum_transformed_dgts += x;

    int luhn_num = 10 - sum_transformed_dgts % 10;
    return luhn_num;
  }

  static bool validate_check_dgt(long int num) {
    int check_dgt = num % 10;
    int luhn_num = Luhn::calculate_check_dgt(num / 10);
    bool check_dgt_correct = check_dgt == luhn_num;
    return check_dgt_correct;
  }
};

class Verhoeff: public AbstractChecksum {
  /*
   * https://en.wikipedia.org/wiki/Verhoeff_algorithm
   *
   * Can be performed using three tables:
   * d: Cayley table of the dihedral group D_5
   * inv: multiplicative inverse of the index
   * p: specific permutation applied iteratively
   */
  static constexpr int d[10][10] = {
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
  static constexpr int inv[10] = {0, 4, 3, 2, 1, 5, 6, 7, 8, 9};
  static constexpr int p[8][10] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 5, 7, 6, 2, 8, 3, 0, 9, 4},
    {5, 8, 0, 3, 7, 9, 6, 1, 4, 2},
    {8, 9, 1, 6, 0, 4, 3, 5, 2, 7},
    {9, 4, 5, 3, 1, 2, 6, 8, 7, 0},
    {4, 2, 8, 6, 5, 7, 3, 9, 0, 1},
    {2, 7, 9, 3, 8, 0, 6, 4, 1, 5},
    {7, 0, 4, 6, 9, 1, 3, 2, 5, 8}
  };

  public:
    static int calculate_check_dgt(long int num) {
      // "append zero" before performing calculation
      std::vector < int > num_dgts_plus = get_digit_vec(10 * num, true);
      // For each index i=1,2,...,len(num_dgts): c = d(c, p(i mod 8, num[i]))
      int c = 0;
      for (auto idx = 0; idx != num_dgts_plus.size(); idx++) {
        c = d[c][p[idx][num_dgts_plus[idx] % 8]];
      }
      int check_dgt = inv[c];
      return check_dgt;
    }

  static bool validate_check_dgt(long int num) {
    std::vector < int > num_dgts = get_digit_vec(num, true);
    // For each index i=1,2,...,len(num_dgts): c = d(c, p(i mod 8, num[i]))
    int c = 0;
    for (auto idx = 0; idx != num_dgts.size(); idx++) {
      c = d[c][p[idx][num_dgts[idx] % 8]];
    }
    // *num* is valid iff c=0
    bool check_dgt_correct = c == 0;
    return check_dgt_correct;
  }
};

class Damm: public AbstractChecksum {
  /*
   * https://en.wikipedia.org/wiki/Damm_algorithm
   * Other quasigroup tables are possible
   */
  static constexpr int quasigroup_tbl[10][10] = {
    {0, 3, 1, 7, 5, 9, 8, 6, 4, 2},
    {7, 0, 9, 2, 1, 5, 4, 8, 6, 3},
    {4, 2, 0, 6, 8, 7, 1, 3, 5, 9},
    {1, 7, 5, 0, 9, 8, 3, 4, 2, 6},
    {6, 1, 2, 3, 0, 4, 5, 9, 7, 8},
    {3, 6, 7, 4, 2, 0, 9, 5, 8, 1},
    {5, 8, 6, 9, 7, 2, 0, 1, 3, 4},
    {8, 9, 4, 5, 3, 6, 2, 0, 1, 7},
    {9, 4, 3, 8, 6, 1, 7, 2, 0, 5},
    {2, 5, 8, 1, 4, 3, 6, 7, 9, 0}
  };

  public:
    static int calculate_check_dgt(long int num) {
      std::vector<int> num_dgts = get_digit_vec(num);

      int n = 0;
      for (auto it = num_dgts.begin(); it != num_dgts.end(); it++) {
        n = quasigroup_tbl[n][*it];
      }
      return n;
    }

    static bool validate_check_dgt(long int num) {
      int n = Damm::calculate_check_dgt(num);
      bool check_dgt_correct = n == 0;
      return check_dgt_correct;
    }
};
