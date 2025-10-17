// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/biconnected_components
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#include "../../src/graph/vbcc.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  VBCC vbcc(n);
  for (int _ = 0; _ < m; _++) {
    int u, v;
    cin >> u >> v;
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
