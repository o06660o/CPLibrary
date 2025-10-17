// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/biconnected_components
#include <bits/stdc++.h>
#define PUSHB push_back
using namespace std;
using pii = pair<int, int>;
using ll = long long;

#include "../../src/graph/vbcc.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), m = read();
  using ll = long long;
  VBCC vbcc(n);
  for (int _ = 0; _ < m; _++) {
    int u = read(), v = read();
    vbcc.adde(u, v);
  }
  int N = vbcc.work();
  cout << N << "\n";
  for (int i = 0; i < N; i++) {
    const auto& arr = vbcc.vbccs[i];
    assert(!arr.empty());
    cout << arr.size();
    for (int v : arr) cout << " " << v;
    cout << "\n";
  }
  return 0;
}
