template <typename T>
struct FenwickTree {
  FenwickTree(int n) : n(n), c(n) {}
  void add(int pos, T x) {
    for (int i = pos + 1; i <= n; i += i & -i) c[i - 1] += x;
  }
  T pref(int r) const {
    T ret = 0;
    for (int i = r; i > 0; i -= i & -i) ret += c[i - 1];
    return ret;
  }
  T sum(int l, int r) const { return pref(r) - pref(l); }

 private:
  int n;
  vector<T> c;
};
