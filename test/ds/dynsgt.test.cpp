// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_range_composite
#include <bits/stdc++.h>
#define PUSHB push_back
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/ds/dynsgt.hpp"
#include "../../src/math/modint.hpp"
#include "../../src/misc/read.hpp"

struct Info_ {
  mint a = 1, b = 0;
  friend Info_ operator+(const Info_& lhs, const Info_& rhs) {
    return {lhs.a * rhs.a, lhs.b * rhs.a + rhs.b};
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  vector<Info_> a(n);
  for (auto& x : a) {
    x.a = read(), x.b = read();
  }
  SegTree sgt(a);
  while (q--) {
    int op = read();
    if (op == 0) {
      int pos = read(), c = read(), d = read();
      sgt.set(pos, {c, d});
    } else {
      int l = read(), r = read(), x = read();
      auto [A, B] = sgt.sum(l, r);
      cout << (A * x + B).data << "\n";
    }
  }
  return 0;
}
