// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/factorize
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

#include "../../src/math/pollardrho.hpp"

void solve() {
  ll n;
  cin >> n;
  auto factors = breakdown(n);
  cout << factors.size();
  for (ll f : factors) {
    cout << " " << f;
  }
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
