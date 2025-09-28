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
