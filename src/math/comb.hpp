#include "modint.hpp"
vector<mint> fac(1, 1), ifac(1, 1);
void ensure_binom(int m) {
  int n = fac.size();
  if (m < n) return;
  fac.resize(m + 1), ifac.resize(m + 1);
  for (int i = n; i <= m; i++) fac[i] = fac[i - 1] * i;
  ifac[m] = fac[m].inv();
  for (int i = m; i > n; i--) ifac[i - 1] = ifac[i] * i;
}
mint binom(ll n, ll m) {
  if (n < m || m < 0) return 0;
  ensure_binom(n);
  return fac[n] * ifac[m] * ifac[n - m];
}
vector<vector<mint>> init_binom_table(int n) {
  vector<vector<mint>> binom(n + 1, vector<mint>(n + 1, 0));
  binom[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    binom[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
    }
  }
  return binom;
}
