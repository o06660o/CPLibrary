#include "../ds/sgt.hpp"
struct HLD {
  struct Node {
    ll data = 0;
    friend Node operator+(Node lhs, Node rhs) { return {lhs.data + rhs.data}; }
  };
  SegTree<Node> sgt = 0;
  int n, cur_dfn;
  vector<int> fa, dep, siz, hson;
  vector<int> dfn, rdfn, top;
  vector<vector<int>> G;
  HLD(int n)
      : n(n), fa(n, -1), dep(n), siz(n), hson(n, -1), dfn(n), rdfn(n), top(n),
        G(n) {}
  void adde(int u, int v) { G[u].PUSHB(v), G[v].PUSHB(u); }
  void init_dfn(int root) { cur_dfn = 0, dfs1(root, -1), dfs2(root, root); }
  void init_sgt(const vector<int>& a) {
    vector<Node> b(n);
    for (int i = 0; i < n; i++) b[dfn[i]].data = a[i];
    sgt = SegTree(b);
  }
  int lca(int u, int v) const {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
  void add(int p, int x) {
    Node qry = sgt.query(dfn[p], dfn[p] + 1);
    qry.data += x;
    sgt.set(dfn[p], qry);
  }
  ll query(int u, int v) {
    Node ret;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      ret = ret + sgt.query(dfn[top[u]], dfn[u] + 1);
      u = fa[top[u]];
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    ret = ret + sgt.query(dfn[u], dfn[v] + 1);
    return ret.data;
  }

 private:
  void dfs1(int u, int fa_) {
    fa[u] = fa_;
    siz[u] = 1;
    for (int v : G[u]) {
      if (v == fa_) continue;
      dep[v] = dep[u] + 1;
      dfs1(v, u);
      siz[u] += siz[v];
      if (hson[u] == -1 || siz[v] > siz[hson[u]]) hson[u] = v;
    }
  }
  void dfs2(int u, int top_) {
    dfn[u] = cur_dfn;
    rdfn[cur_dfn++] = u;
    top[u] = top_;
    if (hson[u] != -1) dfs2(hson[u], top_);
    for (int v : G[u])
      if (v != fa[u] && v != hson[u]) dfs2(v, v);
  }
};
