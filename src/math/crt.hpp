// 求解线性同余方程组 $x \equiv a_i \pmod{p_i}$, 结果模 $M$ 同余.
#include "modint.hpp"
ll getinv(ll a, ll mod) {
  ll x, y;
  if (mint::exgcd(a, mod, x, y) != 1) return -1;
  return (x + mod) % mod;
}
pll crt(const vector<int>& a, const vector<int>& p) {
  assert(a.size() == p.size());
  ll ret = 0, M = 1;
  for (int x : p) M *= x;
  for (int i = 0; i < int(a.size()); i++) {
    ll m = M / p[i], inv = getinv(m, p[i]);
    ret = (ret + i128(a[i]) * m * inv % M) % M;
  }
  return {ret, M};
}
