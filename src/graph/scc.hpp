// 有向图的强连通分量. 返回强联通分量个数, 点对应的强连通分量编号在 `sccid` 中.
struct SCC {
  int n, cur_dfn, cur_scc;
  stack<int> stk;
  vector<int> dfn, low, sccid;
  vector<vector<int>> G;
  SCC(int n) : n(n), dfn(n, -1), low(n), sccid(n, -1), G(n) {}
  void adde(int u, int v) { G[u].push_back(v); }
  int work() {
    cur_dfn = cur_scc = 0;
    for (int i = 0; i < n; i++)
      if (dfn[i] == -1) tarjan(i);
    assert(stk.empty());
    return cur_scc;
  }

 private:
  void tarjan(int u) {
    dfn[u] = low[u] = cur_dfn++, stk.push(u);
    for (int v : G[u]) {
      if (dfn[v] == -1) {
        tarjan(v), low[u] = min(low[u], low[v]);
      } else if (sccid[v] == -1) {
        low[u] = min(low[u], dfn[v]);
      }
    }
    if (dfn[u] == low[u]) {
      int v;
      do {
        v = stk.top(), stk.pop(), sccid[v] = cur_scc;
      } while (v != u);
      cur_scc++;
    }
  }
};
