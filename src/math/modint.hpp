template <unsigned MOD>
struct ModInt {
  unsigned data;
  ModInt(ll v = 0) : data(norm(v % MOD)) {}
  ModInt operator-() const { return MOD - data; }
  ModInt& operator+=(const ModInt& rhs) {
    data = norm(data + rhs.data);
    return *this;
  }
  ModInt& operator-=(const ModInt& rhs) {
    data = norm(data - rhs.data);
    return *this;
  }
  ModInt& operator*=(const ModInt& rhs) {
    data = ull(data) * rhs.data % MOD;
    return *this;
  }
  ModInt& operator/=(const ModInt& rhs) {
    data = ull(data) * rhs.inv() % MOD;
    return *this;
  }
  friend ModInt operator+(ModInt lhs, const ModInt& rhs) { return lhs += rhs; }
  friend ModInt operator-(ModInt lhs, const ModInt& rhs) { return lhs -= rhs; }
  friend ModInt operator*(ModInt lhs, const ModInt& rhs) { return lhs *= rhs; }
  friend ModInt operator/(ModInt lhs, const ModInt& rhs) { return lhs /= rhs; }
  unsigned inv() const {
    int a = data, b = MOD, x = 1, y = 0, q;
    while (b) {
      q = a / b;
      swap(a -= q * b, b);
      swap(x -= q * y, y);
    }
    assert(a == 1);  // Inverse does not exist if a != 1.
    return norm(x);
  }
  ModInt pow(ull n) const {
    unsigned ret = 1, base = data;
    for (; n; n /= 2) {
      if (n & 1) ret = ull(ret) * base % MOD;
      base = ull(base) * base % MOD;
    }
    return ret;
  }

 private:
  static unsigned norm(unsigned x) {
    if ((x >> (8 * sizeof(unsigned) - 1)) & 1) x += MOD;
    return x >= MOD ? x -= MOD : x;
  }
};
constexpr unsigned MOD = 998244353;
using mint = ModInt<MOD>;

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
  assert(n <= 5e7 && m <= 5e7);
  ensure_binom(n);
  return fac[n] * ifac[m] * ifac[n - m];
}
