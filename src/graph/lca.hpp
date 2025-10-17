// 时间复杂度: 预处理 $\mathcal{O}(n \log n)$; 查询 $\mathcal{O}(1)$
struct LCA {
  int n, m, cur_dfn = 0;
  vector<int> dfn, dep;
  vector<vector<int>> G, st;
  LCA(int n)
      : n(n), m(32 - __builtin_clz(n)), dfn(n, -1), dep(n), G(n),
        st(m, vector<int>(n)) {}
  void adde(int u, int v) { G[u].PUSHB(v), G[v].PUSHB(u); }
  void work(int root) {
    dfs(root, root);
    for (int j = 1; j < m; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[j][i] = op4st(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
  }
  int query(int u, int v) const {
    if (u == v) return u;
    if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
    int q = __lg(v - u);
    return op4st(st[q][u + 1], st[q][v + 1 - (1 << q)]);
  }

 private:
  int op4st(int u, int v) const { return dfn[u] < dfn[v] ? u : v; }
  void dfs(int u, int fa_) {
    st[0][dfn[u] = cur_dfn++] = fa_;
    for (int v : G[u])
      if (v != fa_) dep[v] = dep[u] + 1, dfs(v, u);
  }
};
