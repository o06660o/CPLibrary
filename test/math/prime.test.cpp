// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_primes
#include <bits/stdc++.h>
#define PUSHB push_back
#define ALL(a) (a).begin(), (a).end()
using namespace std;

constexpr int MAXN = 5e8 + 5;
#include "../../src/math/prime.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init_prime_table();
  int n, a, b;
  cin >> n >> a >> b;
  int ptr = upper_bound(ALL(primes), n) - primes.begin();
  int m = (ptr - b + a - 1) / a;
  cout << ptr << " " << m << "\n";
  for (int i = 0; a * i + b < ptr; i++) {
    cout << primes[a * i + b] << " \n"[i + 1 == m];
  }
  return 0;
}
