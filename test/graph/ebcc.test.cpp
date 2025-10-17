// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_edge_connected_components
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#include "../../src/graph/ebcc.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  EBCC ebcc(n);
  for (int _ = 0; _ < m; _++) {
    int u, v;
    cin >> u >> v;
    ebcc.adde(u, v);
  }
  int N = ebcc.work();
  vector<vector<int>> ebccvtx(N);
  for (int v = 0; v < n; v++) ebccvtx[ebcc.ebccid[v]].PUSHB(v);
  cout << N << "\n";
  for (int i = 0; i < N; i++) {
    assert(!ebccvtx[i].empty());
    cout << ebccvtx[i].size();
    for (int v : ebccvtx[i]) cout << " " << v;
    cout << "\n";
  }
  return 0;
}
