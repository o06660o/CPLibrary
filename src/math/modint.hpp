template <unsigned MOD>
struct ModInt {
  unsigned data = 0;
  ModInt(ll v) : data(norm(v % MOD)) {}
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
    int x, y;  // Inverse does not exist if gcd(data, MOD) != 1.
    assert(exgcd(data, MOD, x, y) == 1);
    return norm(x);
  }
  ModInt pow(ull n) const { return pow_mod(data, n); }

 private:
  static int exgcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    while (b) {
      int q = a / b;
      swap(a -= q * b, b);
      swap(x -= q * y, y);
    }
    return a;
  }
  static ull pow_mod(ull a, ull n) {
    ull ret = 1;
    for (; n; n /= 2) {
      if (n & 1) ret = ret * a % MOD;
      a = a * a % MOD;
    }
    return ret;
  }
  static unsigned norm(unsigned x) {
    if ((x >> (8 * sizeof(unsigned) - 1)) & 1) x += MOD;
    return x >= MOD ? x -= MOD : x;
  }
};
constexpr unsigned MOD = 998244353;
using mint = ModInt<MOD>;
