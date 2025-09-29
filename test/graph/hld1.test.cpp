// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;

#include "../../src/graph/hld.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  HLD hld(n);
  for (int i = 1; i < n; i++) {
    int p = read();
    hld.adde(i, p);
  }
  hld.init_dfn(0);
  while (q--) {
    int u = read(), v = read();
    cout << hld.lca(u, v) << "\n";
  }
  return 0;
}
