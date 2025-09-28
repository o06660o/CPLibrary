// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_range_sum
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../src/ds/ft.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  FenwickTree<ll> fw(n);
  for (int i = 0; i < n; i++) {
    int a = read();
    fw.add(i, a);
  }
  while (q--) {
    int op = read();
    if (op == 0) {
      int p = read(), x = read();
      fw.add(p, x);
    } else if (op == 1) {
      int l = read(), r = read();
      cout << fw.sum(l, r) << "\n";
    }
  }
  return 0;
}
