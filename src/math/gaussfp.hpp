//  求解线性方程组 $A \boldsymbol{x} = \boldsymbol{b}$. 时间复杂度
//  $\mathcal{O}(n \times m \times min(n, m))$.
//  - 返回 `0` 说明有唯一解, 存储在 `x` 中.
//  - 返回正数 `n` 说明有无穷多解, `n` 是自由变量的个数, `x` 存储了一个解,
//    自由变量设为 $0$.
//  - 返回 `-1` 说明无解.
template <typename fp>
int gauss_fp(const vector<vector<fp>>& A, vector<fp>& x, const vector<fp>& b) {
  const fp EPS = numeric_limits<fp>::epsilon() * fp(1e2);
  int n = A.size(), m = int(A[0].size());
  assert(int(b.size()) == n);
  vector<vector<fp>> aug(n, vector<fp>(m + 1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      aug[i][j] = A[i][j];
    }
    aug[i][m] = b[i];
  }
  vector<int> where(m, -1);
  int row = 0;
  for (int col = 0; col < m && row < n; col++) {
    int sel = row;
    for (int i = row; i < n; i++) {
      if (abs(aug[i][col]) > abs(aug[sel][col])) {
        sel = i;
      }
    }
    if (abs(aug[sel][col]) <= EPS) continue;
    swap(aug[sel], aug[row]);
    where[col] = row;
    for (int j = m; j >= col; j--) {
      for (int i = row + 1; i < n; i++) {
        aug[i][j] -= aug[i][col] / aug[row][col] * aug[row][j];
      }
    }
    row++;
  }
  for (int i = row; i < n; i++) {
    bool all_zero = true;
    for (int j = 0; j < m; j++) {
      if (abs(aug[i][j]) > EPS) {
        all_zero = false;
        break;
      }
    }
    if (all_zero && abs(aug[i][m]) > EPS) return -1;
  }
  x.assign(m, fp(0));
  for (int j = m - 1; j >= 0; j--) {
    if (where[j] == -1) continue;
    int r = where[j];
    fp sum = aug[r][m];
    for (int k = j + 1; k < m; k++) {
      sum -= aug[r][k] * x[k];
    }
    x[j] = sum / aug[r][j];
  }
  int free_vars = 0;
  for (int j = 0; j < m; j++) {
    if (where[j] == -1) {
      free_vars++;
    }
  }
  return free_vars;
};
