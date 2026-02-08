constexpr ull BASE = 10453;
using hash2 = array<ull, 2>;
constexpr hash2 MOD = {100000000000861, 100000000000963};
static vector<hash2> pow_base = {{1, 1}};
void ensure_pow_base(int len) {
  int m = pow_base.size();
  if (m > len) return;
  pow_base.resize(len + 1);
  for (int i = m; i <= len; i++)
    for (int k = 0; k < 2; k++)
      pow_base[i][k] = pow_base[i - 1][k] * BASE % MOD[k];
}
hash2 get_hash(const string& s) {
  hash2 ret = {};
  for (char ch : s)
    for (int k = 0; k < 2; k++) ret[k] = (ret[k] * BASE + ch) % MOD[k];
  return ret;
}
vector<hash2> get_pref(const string& s) {
  int n = s.size();
  vector<hash2> ret(n + 1);
  for (int i = 0; i < n; i++)
    for (int k = 0; k < 2; k++)
      ret[i + 1][k] = (ret[i][k] * BASE + s[i]) % MOD[k];
  return ret;
}
vector<hash2> get_suf(const string& s) {
  int n = s.size();
  ensure_pow_base(n);
  vector<hash2> ret(n + 1);
  for (int i = n - 1; i >= 0; i--)
    for (int k = 0; k < 2; k++)
      ret[i][k] =
          (ret[i + 1][k] + (i128)s[i] * pow_base[n - 1 - i][k]) % MOD[k];
  return ret;
}
hash2 concat(const hash2& lhs, const hash2& rhs, ull rhs_len) {
  ensure_pow_base(rhs_len);
  hash2 ret = {};
  for (int k = 0; k < 2; k++)
    ret[k] = ((i128)lhs[k] * pow_base[rhs_len][k] + rhs[k]) % MOD[k];
  return ret;
}
