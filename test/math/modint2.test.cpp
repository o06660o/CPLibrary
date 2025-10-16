// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/math/modint.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll a, b, x, y;
  cin >> a >> b;
  mint::exgcd(a, b, x, y);
  cout << x << " " << y << "\n";
  return 0;
}
