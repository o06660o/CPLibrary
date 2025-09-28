#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <bits/stdc++.h>
using namespace std;

#include "../../../src/ds/dsu.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  while (q--) {
    int op, u, v;
    cin >> op >> u >> v;
    if (op == 0) {
      dsu.merge(u, v);
    } else if (op == 1) {
      cout << dsu.same(u, v) << "\n";
    }
  }
  return 0;
}
