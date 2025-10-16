// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/math/modint.hpp"

using mint107 = ModInt<1000000007>;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int m, n;
  cin >> m >> n;
  cout << mint107(m).pow(n).data << "\n";
  return 0;
}
