#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../src/misc/inthash.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int q;
  cin >> q;
  unordered_map<ll, ll, IntHash> mp;
  while (q--) {
    int op;
    cin >> op;
    if (op == 0) {
      ll k, v;
      cin >> k >> v;
      mp[k] = v;
    } else if (op == 1) {
      ll k;
      cin >> k;
      cout << mp[k] << "\n";
    }
  }
  return 0;
}
