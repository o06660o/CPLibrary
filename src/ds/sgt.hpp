template <typename Node>
struct SegTree {
  int n, _pos, _l, _r;
  Node _node;
  vector<Node> tree;
  SegTree(int n) : n(n), tree(4 * n) {}
  SegTree(const vector<Node>& a) : SegTree(a.size()) { build(1, 0, n, a); }
  void set(int pos, Node node) { _pos = pos, _node = node, set(1, 0, n); }
  Node query(int l, int r) { return _l = l, _r = r, query(1, 0, n); }

 private:
  void build(int p, int pl, int pr, const vector<Node>& a) {
    if (pr - pl == 1) return tree[p] = a[pl], void();
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    build(ls, pl, mid, a), build(rs, mid, pr, a);
    tree[p] = tree[ls] + tree[rs];
  }
  void set(int p, int pl, int pr) {
    if (pr - pl == 1) return tree[p] = _node, void();
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    _pos < mid ? set(ls, pl, mid) : set(rs, mid, pr);
    tree[p] = tree[ls] + tree[rs];
  }
  Node query(int p, int pl, int pr) {
    if (pl >= _r || pr <= _l) return Node();
    if (_l <= pl && pr <= _r) return tree[p];
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    return query(ls, pl, mid) + query(rs, mid, pr);
  }
};
struct Node {
  int data = 2e9;
  friend Node operator+(const Node& lhs, const Node& rhs) {
    return {min(lhs.data, rhs.data)};
  }
};
