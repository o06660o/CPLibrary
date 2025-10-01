// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/ds/lzsgt.hpp"
#include "../../src/math/modint.hpp"
#include "../../src/misc/read.hpp"

struct Node_ {
  mint sum = 0;
  int len = 0;
  friend Node_ operator+(const Node_& lhs, const Node_& rhs) {
    return {lhs.sum + rhs.sum, lhs.len + rhs.len};
  }
};
struct Tag_ {
  mint b = 1, c = 0;
  Tag_ operator+=(const Tag_& rhs) {
    b *= rhs.b;
    c = c * rhs.b + rhs.c;
    return *this;
  }
};
void fn_(const Tag_& f, Node_& x) { x.sum = x.sum * f.b + f.c * x.len; }

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  vector<Node_> a(n);
  for (auto& [sum, len] : a) {
    sum.data = read();
    len = 1;
  }
  SegTree<Node_, Tag_, fn_> sgt(a);
  while (q--) {
    int op = read(), l = read(), r = read();
    if (op == 0) {
      int b = read(), c = read();
      sgt.apply(l, r, {b, c});
    } else {
      cout << sgt.query(l, r).sum.data << "\n";
    }
  }
  return 0;
}
