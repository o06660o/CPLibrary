template <unsigned MOD>
struct ModInt {
  unsigned data;
  ModInt(ll v = 0) : data(norm(v % MOD)) {}
  ModInt operator-() const { return MOD - data; }
  ModInt& operator+=(ModInt rhs) { return data = norm(data + rhs.data), *this; }
  ModInt& operator-=(ModInt rhs) { return data = norm(data - rhs.data), *this; }
  ModInt& operator*=(ModInt rhs) {
    return data = ull(data) * rhs.data % MOD, *this;
  }
  ModInt& operator/=(ModInt rhs) {
    return data = ull(data) * rhs.inv() % MOD, *this;
  }
  friend ModInt operator+(ModInt lhs, ModInt rhs) { return lhs += rhs; }
  friend ModInt operator-(ModInt lhs, ModInt rhs) { return lhs -= rhs; }
  friend ModInt operator*(ModInt lhs, ModInt rhs) { return lhs *= rhs; }
  friend ModInt operator/(ModInt lhs, ModInt rhs) { return lhs /= rhs; }
  unsigned inv() const {
    ll x, y;  // Inverse does not exist if gcd(data, MOD) != 1.
    assert(exgcd(data, MOD, x, y) == 1);
    return norm(x);
  }
  ModInt pow(ull n) const { return pow_mod(data, n, MOD); }
  static ll exgcd(ll a, ll b, ll& x, ll& y) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1;
    while (b) {
      ll q = a / b;
      swap(a -= q * b, b);
      swap(x -= q * x1, x1);
      swap(y -= q * y1, y1);
    }
    return a;
  }
  static unsigned pow_mod(unsigned a, ull n, unsigned p) {
    unsigned ret = 1;
    for (; n; n /= 2) {
      if (n & 1) ret = ull(ret) * a % p;
      a = ull(a) * a % p;
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
