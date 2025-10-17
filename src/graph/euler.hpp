// 无向图欧拉回路或路径, 时间复杂度 $\mathcal{O}(n + m)$.
struct Euler {
  int n, m = 0;
  vector<char> used;
  vector<int> cur_e, path, epath;
  vector<vector<pii>> G;
  Euler(int n) : n(n), cur_e(n), G(n) {}
  void adde(int u, int v) { G[u].PUSHB({v, m}), G[v].PUSHB({u, m++}); }
  int work() {
    if (m == 0) return path.PUSHB(0), 0;
    used.assign(m, 0);
    vector<int> odd, even;
    for (int i = 0; i < n; i++)
      if (!G[i].empty()) G[i].size() & 1 ? odd.PUSHB(i) : even.PUSHB(i);
    if (odd.size() == 1 || odd.size() > 2) return -1;
    odd.empty() ? dfs(even[0]) : dfs(odd[0]);
    reverse(ALL(path)), reverse(ALL(epath));
    return int(path.size()) == m + 1 ? 0 : -1;
  }

 private:
  void dfs(int u) {
    for (int& i = cur_e[u]; i < int(G[u].size());) {
      auto [v, e] = G[u][i++];
      if (used[e]) continue;
      used[e] = 1, dfs(v), epath.PUSHB(e);
    }
    path.PUSHB(u);
  }
};
