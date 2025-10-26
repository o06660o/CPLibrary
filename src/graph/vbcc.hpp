// 无向图的点双连通分量. 返回双联通分量个数, 点对应的连通分量在 `vbccs` 中.
struct VBCC {
  int n, m = 0, cur_dfn;
  vector<char> iscut;
  stack<int> stk;
  vector<int> dfn, low;
  vector<vector<int>> vbccs;
  vector<vector<pii>> G;
  VBCC(int n) : n(n), iscut(n), dfn(n, -1), low(n), G(n) {}
  void adde(int u, int v) { G[u].PUSHB({v, m}), G[v].PUSHB({u, m++}); }
  int work() {
    for (int i = 0; i < n; i++)
      if (dfn[i] == -1) tarjan(i, -1), stk.pop();
    assert(stk.empty());
    return vbccs.size();
  }

 private:
  void tarjan(int u, int fa_e) {
    dfn[u] = low[u] = cur_dfn++, stk.push(u);
    int sons = 0, flag = 0, tmp;
    for (const auto& [v, e] : G[u]) {
      if (dfn[v] == -1) {
        tarjan(v, e), sons++, low[u] = min(low[u], low[v]);
        if (low[v] >= dfn[u]) {
          flag++, vbccs.PUSHB({});
          if (fa_e != -1 || flag > 1) iscut[u] = 1;
          do {
            tmp = stk.top(), stk.pop(), vbccs.rbegin()->PUSHB(tmp);
          } while (tmp != v);
          vbccs.rbegin()->PUSHB(u);
        }
      } else if (e != fa_e) {
        low[u] = min(low[u], dfn[v]);
      }
    }
    if (fa_e == -1 && sons == 0) vbccs.PUSHB({u});
  }
};
