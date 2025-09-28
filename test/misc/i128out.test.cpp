// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/many_aplusb
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

#include "../../src/misc/i128out.hpp"
#include "../../src/misc/read.hpp"

void solve() {
  ll a = read(), b = read();
  cout << i128(a + b) << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int tt = read();
  while (tt--) {
    solve();
  }
  return 0;
}
