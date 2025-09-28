// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/associative_array
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../src/misc/inthash.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int q = read();
  unordered_map<ll, ll, IntHash> mp;
  while (q--) {
    int op = read();
    if (op == 0) {
      ll k = read(), v = read();
      mp[k] = v;
    } else if (op == 1) {
      ll k = read();
      cout << mp[k] << "\n";
    }
  }
  return 0;
}
