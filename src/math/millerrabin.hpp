// 时间复杂度: $\mathcal{O}(k \log n)$，目前 $k = 9$ 足以判定 $64$ 位整数.
#include "pow_mod_ll.hpp"
bool isprime(ll n) {
  if (n < 2) return 0;
  int s = __builtin_ctzll(n - 1);
  ll d = (n - 1) >> s;
  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
    if (a == n) return 1;
    ll x = pow_mod_ll(a, d, n);
    if (x == 1 || x == n - 1) continue;
    bool ok = 0;
    for (int i = 0; i + 1 < s; i++) {
      x = i128(x) * x % n;
      if (x == n - 1) {
        ok = 1;
        break;
      }
    }
    if (!ok) return 0;
  }
  return 1;
}
