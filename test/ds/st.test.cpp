// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../src/ds/st.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  vector<int> a(n);
  for (auto& x : a) {
    x = read();
  }
  SparseTable st(a, [](int lhs, int rhs) { return min(lhs, rhs); });
  while (q--) {
    int l = read(), r = read();
    cout << st.query(l, r) << "\n";
  }
  return 0;
}
