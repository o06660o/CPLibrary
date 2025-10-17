// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/eulerian_trail_undirected
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using pii = pair<int, int>;

#include "../../src/graph/euler.hpp"

void solve() {
  int n, m;
  cin >> n >> m;
  map<pii, int> mp;
  Euler euler(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    mp[{u, v}] = mp[{v, u}] = i;
    euler.adde(u, v);
  }
  int resp = euler.work();
  if (resp == -1) {
    cout << "No\n";
  } else {
    cout << "Yes\n";
    for (int i = 0; i <= m; i++) cout << euler.path[i] << " \n"[i == m];
    for (int i = 0; i < m; i++) cout << euler.epath[i] << " \n"[i + 1 == m];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}
