// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;

#include "../../src/graph/lca.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  LCA lca(n);
  for (int i = 1; i < n; i++) {
    int p = read();
    lca.adde(i, p);
  }
  lca.work(0);
  while (q--) {
    int u = read(), v = read();
    cout << lca.query(u, v) << "\n";
  }
  return 0;
}
