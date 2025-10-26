// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primality_test
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

#include "../../src/math/millerrabin.hpp"

void solve() {
  ll n;
  cin >> n;
  cout << (isprime(n) ? "Yes\n" : "No\n");
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
