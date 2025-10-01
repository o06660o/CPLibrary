// 时间复杂度: $\mathcal{O}(mf \log n)$.
template <typename T>
struct PrimalDual {
  struct Edge {
    int u, v;
    T cap, cost, flow;
  };
  static constexpr T INF = numeric_limits<T>::max();
  int n, _s, _t;
  vector<int> prev;
  vector<T> h, dist;
  vector<vector<int>> G;
  vector<Edge> E;
  PrimalDual(int n) : n(n), prev(n), h(n), dist(n), G(n) {}
  void adde(int u, int v, T cap, T cost) {
    G[u].PUSHB(E.size()), E.PUSHB({u, v, cap, cost, 0});
    G[v].PUSHB(E.size()), E.PUSHB({v, u, 0, -cost, 0});
  }
  pair<T, T> flow(int s, int t, T maxf = INF) {
    _s = s, _t = t;
    bellman_ford();
    T maxflow = 0, mincost = 0;
    while (maxflow < maxf && dijkstra()) {
      T aug = maxf - maxflow;
      for (int i = 0; i < n; i++)
        if (dist[i] != INF) h[i] += dist[i];
      for (int p = _t; p != _s; p = E[prev[p] ^ 1].v)
        aug = min(aug, E[prev[p]].cap - E[prev[p]].flow);
      for (int p = _t; p != _s; p = E[prev[p] ^ 1].v)
        E[prev[p]].flow += aug, E[prev[p] ^ 1].flow -= aug;
      maxflow += aug, mincost += aug * h[_t];
    }
    return {maxflow, mincost};
  }

 private:
  void bellman_ford() {
    queue<int> que;
    vector<char> in_que(n);
    fill(ALL(h), INF);
    h[_s] = 0;
    in_que[_s] = 1;
    que.push(_s);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      in_que[u] = 0;
      for (int i : G[u]) {
        const auto& [_, v, cap, cost, flow] = E[i];
        if (cap <= flow || h[v] <= h[u] + cost) continue;
        h[v] = h[u] + cost;
        if (!in_que[v]) {
          in_que[v] = 1;
          que.push(v);
        }
      }
    }
  }
  bool dijkstra() {
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> pq;
    fill(ALL(dist), INF);
    dist[_s] = 0;
    pq.push({0, _s});
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (dist[u] != d) continue;
      for (int i : G[u]) {
        auto& [_, v, cap, cost, flow] = E[i];
        if (cap <= flow || dist[v] <= d + cost + h[u] - h[v]) continue;
        dist[v] = d + cost + h[u] - h[v];
        prev[v] = i;
        pq.push({dist[v], v});
      }
    }
    return dist[_t] != INF;
  }
};
