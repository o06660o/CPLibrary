// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primitive_root
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

#include "../../src/math/proot.hpp"

void solve() {
  ll p;
  cin >> p;
  cout << proot(p) << "\n";
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
