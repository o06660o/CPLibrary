#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;

#include "../../../src/graph/dinic.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  Dinic<ll> dinic(n);
  for (int _ = 0; _ < m; _++) {
    int u, v, c;
    cin >> u >> v >> c;
    dinic.adde(u, v, c);
  }
  cout << dinic.flow(0, n - 1) << "\n";
  return 0;
}
