// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/scc
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#include "../../src/graph/scc.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<pii> E(m);
  SCC scc(n);
  for (auto& [u, v] : E) {
    cin >> u >> v;
    scc.adde(u, v);
  }
  int N = scc.work();
  vector<int> indeg(N);
  vector<vector<int>> H(N), sccvtx(N);
  for (int i = 0; i < n; i++) sccvtx[scc.sccid[i]].PUSHB(i);
  for (const auto& [u, v] : E) {
    int su = scc.sccid[u], sv = scc.sccid[v];
    if (su != sv) {
      H[su].PUSHB(sv);
      indeg[sv]++;
    }
  }

  queue<int> que;
  for (int i = 0; i < N; i++) {
    if (indeg[i] == 0) que.push(i);
  }

  vector<int> ans;
  ans.reserve(N);
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    ans.PUSHB(u);
    for (int v : H[u]) {
      if (--indeg[v] == 0) {
        que.push(v);
      }
    }
  }

  cout << N << "\n";
  for (int i : ans) {
    cout << sccvtx[i].size();
    for (int v : sccvtx[i]) cout << " " << v;
    cout << "\n";
  }
  return 0;
}
