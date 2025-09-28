/**
 *  时间复杂度: 一般图 $\mathcal{O}(n^2 m)$, 二分图匹配
 *    $\mathcal{O}(m \sqrt{n}})$, 随机数据表现良好.
 */
template <typename T>
struct Dinic {
  struct Edge {
    int u, v;
    T cap, flow;
  };
  static constexpr T INF = numeric_limits<T>::max();
  vector<vector<int>> G;
  vector<Edge> E;
  Dinic(int n) : G(n), n(n), cur(n), h(n) {}
  void adde(int u, int v, T cap) {
    G[u].PUSHB(E.size()), E.PUSHB({u, v, cap, 0});
    G[v].PUSHB(E.size()), E.PUSHB({v, u, 0, 0});
  }
  T flow(int s_, int t_) {
    s = s_, t = t_;
    T ret = 0;
    while (bfs()) {
      fill(ALL(cur), 0);
      ret += dfs(s, INF);
    }
    return ret;
  }

 private:
  int n, s, t;
  vector<int> cur, h;
  bool bfs() {
    fill(ALL(h), -1);
    queue<int> que;
    h[s] = 0;
    que.push(s);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int i : G[u]) {
        const auto& [_, v, cap, flow] = E[i];
        if (h[v] != -1 || cap <= flow) continue;
        h[v] = h[u] + 1;
        que.push(v);
        if (v == t) return true;
      }
    }
    return false;
  }
  T dfs(int u, T up) {
    if (u == t) return up;
    T rest = up;
    for (int& i = cur[u]; i < int(G[u].size()); i++) {
      auto& [_, v, cap, flow] = E[G[u][i]];
      if (h[v] != h[u] + 1 || cap <= flow) continue;
      T f = dfs(v, min(rest, cap - flow));
      if (f <= 0) continue;
      flow += f;
      E[G[u][i] ^ 1].flow -= f;
      rest -= f;
      if (rest == 0) break;
    }
    return up - rest;
  }
};
