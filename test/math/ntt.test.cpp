// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#include "../../src/math/ntt.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read(), m = read();
  Poly F, G;
  F.data.resize(n);
  for (int i = 0; i < n; i++) F.data[i] = read();
  G.data.resize(m);
  for (int i = 0; i < m; i++) G.data[i] = read();
  Poly H = F * G;
  for (int i = 0; i < n + m - 1; i++) {
    cout << H.data[i].data << " \n"[i == n + m - 2];
  }
  return 0;
}
