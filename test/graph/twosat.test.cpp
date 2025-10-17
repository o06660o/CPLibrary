// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_sat
#include <bits/stdc++.h>
#define PUSHB push_back
using namespace std;
using ll = long long;

#include "../../src/graph/twosat.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  for (int _ = 0; _ < 6; _++) getchar();
  int n = read(), m = read();
  TwoSat ts(n);
  for (int _ = 0; _ < m; _++) {
    int a = read(), b = read(), unused = read();
    ts.adde(abs(a) - 1, a > 0, abs(b) - 1, b > 0);
  }
  auto resp = ts.work();
  if (resp) {
    cout << "s SATISFIABLE\n";
    cout << "v";
    for (int i = 0; i < n; i++) {
      cout << " " << (ts.ans[i] ? 1 : -1) * (i + 1);
    }
    cout << " 0\n";
  } else {
    cout << "s UNSATISFIABLE\n";
  }
  return 0;
}
