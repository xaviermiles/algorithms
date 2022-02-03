#pragma once

#include <vector>
#include <algorithm>
#include <sstream>


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

  return digit_vec;
}

std::string join_vec(std::vector<int> vec, std::string sep) {
  /*
   * Join elements of vector, separated by `sep`
   */
  std::stringstream ss;
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i != 0)
      ss << sep;
    ss << vec[i];
  }
  std::string s = ss.str();
  return s;
}
