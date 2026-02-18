// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_affine_range_sum
#include <bits/stdc++.h>
#define PUSHB push_back
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/ds/dynlzsgt.hpp"
#include "../../src/math/modint.hpp"
#include "../../src/misc/read.hpp"

struct Info_ {
  mint sum = 0;
  friend Info_ operator+(const Info_& lhs, const Info_& rhs) {
    return {lhs.sum + rhs.sum};
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
void fn_(Info_& x, const Tag_& f, int len) { x.sum = x.sum * f.b + f.c * len; }

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), q = read();
  SegTree<Info_, Tag_, fn_> sgt(n);
  for (int i = 0; i < n; i++) {
    int x = read();
    sgt.set(i, {x});
  }
  while (q--) {
    int op = read(), l = read(), r = read();
    if (op == 0) {
      int b = read(), c = read();
      sgt.apply(l, r, {b, c});
    } else {
      cout << sgt.sum(l, r).sum.data << "\n";
    }
  }
  return 0;
}
