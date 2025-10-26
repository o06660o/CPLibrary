// 时间复杂度: 期望 $\mathcal{O}(n^{1/4})$
#include "millerrabin.hpp"
ll pollard_single(ll n) {
  if (n % 2 == 0) return 2;
  if (isprime(n)) return n;
  ll st = 0;
  auto f = [&](ll x) -> ll { return (i128(x) * x % n + st) % n; };
  while (true) {
    st++;
    ll x = st, y = f(x);
    while (true) {
      ll p = gcd(y - x + n, n);
      if (p == 0 || p == n) break;
      if (p != 1) return p;
      x = f(x), y = f(f(y));
    }
  }
}
vector<ll> breakdown(ll n) {
  if (n == 1) return {};
  ll x = pollard_single(n);
  if (x == n) return {n};
  auto l = breakdown(x), r = breakdown(n / x);
  l.insert(l.end(), ALL(r)), sort(ALL(l));
  return l;
}
