#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;

#include "../../src/graph/primaldual.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, maxf;
  cin >> n >> m >> maxf;
  PrimalDual<ll> pd(n);
  for (int _ = 0; _ < m; _++) {
    int u, v, c, w;
    cin >> u >> v >> c >> w;
    pd.adde(u, v, c, w);
  }
  auto [maxflow, mincost] = pd.flow(0, n - 1, maxf);
  cout << (maxflow == maxf ? mincost : -1) << "\n";
  return 0;
}
