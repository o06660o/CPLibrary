/**
 *  `fasiz[i]` 非负时表示 `i` 的父节点, 否则表示 `i` 所在集合的大小的负值.
 */
struct DSU {
  vector<int> fasiz;
  DSU(int n) : fasiz(n, -1) {}
  int find(int x) { return fasiz[x] < 0 ? x : fasiz[x] = find(fasiz[x]); }
  bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (-fasiz[x] < -fasiz[y]) swap(x, y);
    fasiz[x] += fasiz[y];
    fasiz[y] = x;
    return true;
  }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return -fasiz[find(x)]; }
};
