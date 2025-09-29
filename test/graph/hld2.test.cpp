// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum
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
  vector<int> a(n);
  for (auto& x : a) {
    x = read();
  }
  HLD hld(n);
  for (int _ = 0; _ + 1 < n; _++) {
    int u = read(), v = read();
    hld.adde(u, v);
  }
  hld.init_dfn(0);
  hld.init_sgt(a);
  while (q--) {
    int op = read();
    if (op == 0) {
      int p = read(), x = read();
      hld.add(p, x);
    } else {
      int u = read(), v = read();
      cout << hld.query(u, v) << "\n";
    }
  }
  return 0;
}
