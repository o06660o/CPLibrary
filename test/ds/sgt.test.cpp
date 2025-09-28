// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../src/ds/sgt.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  vector<Node> a(n);
  for (auto& x : a) {
    x = read();
  }
  SegTree sgt(a);
  while (q--) {
    int l = read(), r = read();
    cout << sgt.query(l, r).data << "\n";
  }
  return 0;
}
