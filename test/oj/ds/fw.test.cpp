#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "ds/ft.inc"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  FenwickTree<ll> fw(n);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    fw.add(i, a);
  }
  while (q--) {
    int op;
    cin >> op;
    if (op == 0) {
      int p, x;
      cin >> p >> x;
      fw.add(p, x);
    } else if (op == 1) {
      int l, r;
      cin >> l >> r;
      cout << fw.sum(l, r) << "\n";
    }
  }
  return 0;
}
