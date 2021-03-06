// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::min;
using std::minmax;
using std::pair;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
// Return (min, max) pair of elements in A.
pair<int, int> find_min_max(const vector<int>& A) {
  if (A.size() <= 1) {
    return {A.front(), A.front()};
  }

  // Initialize the min and max pair.
  pair<int, int> min_max_pair = minmax(A[0], A[1]);
  for (int i = 2; i + 1 < A.size(); i += 2) {
    pair<int, int> local_pair = minmax(A[i], A[i + 1]);
    min_max_pair = {min(min_max_pair.first, local_pair.first),
                    max(min_max_pair.second, local_pair.second)};
  }
  // Special case: if there is odd number of elements in the array, we still
  // need to compare the last element with the existing answer.
  if (A.size() & 1) {
    min_max_pair = {min(min_max_pair.first, A.back()),
                    max(min_max_pair.second, A.back())};
  }
  return min_max_pair;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = atoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 10000);
      n = dis(gen);
    }
    vector<int> A;
    for (int i = 0; i < n; ++i) {
      uniform_int_distribution<int> dis(0, 999999);
      A.emplace_back(dis(gen));
    }
    pair<int, int> res = find_min_max(A);
    assert(res.first == *min_element(A.cbegin(), A.cend()) &&
           res.second == *max_element(A.cbegin(), A.cend()));
  }
  return 0;
}
