// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/unionfind
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
using namespace std;

#include "../../src/ds/dsu_short.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  while (q--) {
    int op, u, v;
    cin >> op >> u >> v;
    if (op == 0) {
      dsu.fa[dsu.find(u)] = dsu.find(v);
    } else {
      cout << (dsu.find(u) == dsu.find(v)) << "\n";
    }
  }
  return 0;
}
