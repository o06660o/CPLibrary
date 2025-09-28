struct DSU {
  vector<int> fa;
  DSU(int n) : fa(n) { iota(ALL(fa), 0); }
  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
};
