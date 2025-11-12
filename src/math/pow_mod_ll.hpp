ll pow_mod_ll(ll a, ull n, ll p) {
  ll ret = 1;
  for (; n; n /= 2) {
    if (n & 1) ret = i128(ret) * a % p;
    a = i128(a) * a % p;
  }
  return ret;
}
