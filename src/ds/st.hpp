template <typename T, typename Op>
struct SparseTable {
  Op op;
  SparseTable(vector<T> vec, Op op)
      : op(op), n(vec.size()), m(32 - __builtin_clz(n)), data(m, vector<T>(n)) {
    data[0] = move(vec);
    for (int j = 1; j < m; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        data[j][i] = op(data[j - 1][i], data[j - 1][i + (1 << (j - 1))]);
  }
  T query(int l, int r) const {
    int q = __lg(r - l);
    return op(data[q][l], data[q][r - (1 << q)]);
  }

 private:
  int n, m;
  vector<vector<T>> data;
};
