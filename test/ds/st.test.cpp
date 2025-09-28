// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <bits/stdc++.h>
using namespace std;

#include "../../src/ds/st.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (auto& x : a) {
    cin >> x;
  }
  SparseTable st(a, [](int lhs, int rhs) { return min(lhs, rhs); });
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << st.query(l, r) << "\n";
  }
  return 0;
}
