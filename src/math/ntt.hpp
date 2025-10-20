#include "modint.hpp"
template <int MOD = 998244353, int G = 114514, int GI = 137043501>
struct Poly {
  vector<mint> data;

  friend Poly operator*(const Poly& a, const Poly& b) {
    int n = 1, new_sz = a.data.size() + b.data.size() - 1;
    while (n < int(a.data.size() + b.data.size())) n *= 2;
    vector<mint> A = a.data, B = b.data;
    A.resize(n), B.resize(n);
    ntt(A, 1), ntt(B, 1);
    for (int i = 0; i < n; i++) A[i] *= B[i];
    ntt(A, -1);
    A.resize(new_sz);
    return Poly{A};
  }

 private:
  static void ntt(vector<mint>& a, int type) {
    int len = a.size();
    vector<int> rev(len);
    for (int i = 0; i < len; i++) {
      rev[i] = rev[i >> 1] >> 1;
      if (i & 1) rev[i] |= len >> 1;
    }
    for (int i = 0; i < len; i++)
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int n = 2, m = 1; n <= len; n *= 2, m *= 2) {
      mint step = mint(type == 1 ? G : GI).pow((MOD - 1) / n);
      for (int j = 0; j < len; j += n) {
        mint w = 1;
        for (int k = j; k < j + m; k++) {
          mint u = a[k], v = w * a[k + m];
          a[k] = u + v, a[k + m] = u - v, w *= step;
        }
      }
    }
    if (type == -1) {
      mint inv = mint(len).pow(MOD - 2);
      for (int i = 0; i < len; i++) a[i] *= inv;
    }
  }
};
