// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;

#include "../../src/math/xorbasis.hpp"
constexpr int MAXLOG = 32;

void solve() {
  auto init = []() -> pair<XorBasis<MAXLOG>, int> {
    XorBasis<MAXLOG> xb;
    int n;
    cin >> n;
    for (int _ = 0; _ < n; _++) {
      int x;
      cin >> x;
      xb.insert(x);
    }
    return {xb, n};
  };
  auto [xb1, n] = init();
  auto [xb2, m] = init();
  auto xb3 = xb1 & xb2;
  vector<int> ans;
  for (const auto& v : xb3.data) {
    if (v.any()) ans.PUSHB(v.to_ulong());
  }
  cout << ans.size();
  for (int x : ans) cout << " " << x;
  cout << "\n";
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
