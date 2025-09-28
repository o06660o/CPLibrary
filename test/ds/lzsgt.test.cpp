// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/ds/lzsgt.hpp"
#include "../../src/math/modint.hpp"
#include "../../src/misc/read.hpp"

struct Node2 {
  mint sum;
  int len;
  Node2() : sum(0), len(0) {}
  Node2(mint sum, int len) : sum(sum), len(len) {}
  friend Node2 operator+(const Node2& lhs, const Node2& rhs) {
    return {lhs.sum + rhs.sum, lhs.len + rhs.len};
  }
};
struct Tag2 {
  mint b, c;
  Tag2() : b(1), c(0) {}
  Tag2(mint b, mint c) : b(b), c(c) {}
  friend Tag2 operator+(const Tag2& lhs, const Tag2& rhs) {
    return {lhs.b * rhs.b, lhs.c * rhs.b + rhs.c};
  }
};
Node2 fn2(const Tag2& f, const Node2& x) {
  Node2 ret = x;
  ret.sum = ret.sum * f.b + f.c * ret.len;
  return ret;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  vector<Node2> a(n);
  for (auto& [sum, len] : a) {
    sum.data = read();
    len = 1;
  }
  SegTree<Node2, Tag2, fn2> sgt(a);
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
