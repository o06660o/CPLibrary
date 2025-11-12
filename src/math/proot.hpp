// 时间复杂度瓶颈在质因数分解.
#include "pollardrho.hpp"
ll proot(ll p) {
  if (p == 2) return 1;
  ll phi = p - 1;
  auto factors = breakdown(phi);
  factors.erase(unique(ALL(factors)), factors.end());
  for (ll ret = 2; ret <= p; ret++) {
    bool ok = 1;
    for (int i = 0; i < int(factors.size()) && ok; i++) {
      if (pow_mod_ll(ret, phi / factors[i], p) == 1) {
        ok = 0;
        break;
      }
    }
    if (ok) return ret;
  }
  return -1;
}
