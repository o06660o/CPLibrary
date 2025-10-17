// 无向图的边双连通分量. 返回双联通分量个数, 点对应的连通分量编号在 `ebccid` 中.
struct EBCC {
  int n, m = 0, cur_dfn, cur_ebcc;
  vector<char> is_bridge;
  vector<int> dfn, low, ebccid;
  vector<vector<pii>> G;
  EBCC(int n) : n(n), dfn(n, -1), low(n), ebccid(n, -1), G(n) {}
  void adde(int u, int v) { G[u].PUSHB({v, m}), G[v].PUSHB({u, m++}); }
  int work() {
    is_bridge.assign(m, 0);
    for (int i = 0; i < n; i++)
      if (dfn[i] == -1) tarjan(i, -1);
    for (int i = 0; i < n; i++)
      if (ebccid[i] == -1) ebccid[i] = cur_ebcc++, dfs(i);
    return cur_ebcc;
  }

 private:
  void tarjan(int u, int fa_e) {
    dfn[u] = low[u] = cur_dfn++;
    for (const auto& [v, e] : G[u]) {
      if (dfn[v] == -1) {
        tarjan(v, e), low[u] = min(low[u], low[v]);
        if (low[v] > low[u]) is_bridge[e] = 1;
      } else if (e != fa_e) {
        low[u] = min(low[u], dfn[v]);
      }
    }
  }
  void dfs(int u) {
    for (const auto& [v, e] : G[u]) {
      if (ebccid[v] != -1 || is_bridge[e]) continue;
      ebccid[v] = ebccid[u], dfs(v);
    }
  }
};
