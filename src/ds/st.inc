template <typename T, typename Op>
struct SparseTable {
  static constexpr int MAXLOGN = 21;  // Up to 2e6.
  Op op;
  SparseTable(const vector<T>& vec, Op op) : op(op), n(vec.size()), data(n) {
    assert((1 << MAXLOGN) >= n);
    for (int i = 0; i < n; i++) data[i][0] = vec[i];
    for (int j = 1; j <= MAXLOGN; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        data[i][j] = op(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
  }
  T query(int l, int r) const {
    int q = __lg(r - l);
    return op(data[l][q], data[r - (1 << q)][q]);
  }

 private:
  int n;
  vector<array<T, MAXLOGN + 1>> data;
};
