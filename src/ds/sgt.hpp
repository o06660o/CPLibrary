template <typename Node>
struct SegTree {
  SegTree(int n) : n(n), tree(4 * n) {}
  SegTree(const vector<Node>& a) : SegTree(a.size()) { build(1, 0, n, a); }
  void set(int pos, const Node& node) { set(1, 0, n, pos, node); }
  Node query(int l, int r) { return query(1, 0, n, l, r); }

 private:
  int n;
  vector<Node> tree;
  void build(int p, int pl, int pr, const vector<Node>& a) {
    if (pr - pl == 1) return tree[p] = a[pl], void();
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    build(ls, pl, mid, a), build(rs, mid, pr, a);
    tree[p] = tree[ls] + tree[rs];
  }
  void set(int p, int pl, int pr, const int pos, const Node& node) {
    if (pr - pl == 1) return tree[p] = node, void();
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    pos < mid ? set(ls, pl, mid, pos, node) : set(rs, mid, pr, pos, node);
    tree[p] = tree[ls] + tree[rs];
  }
  Node query(int p, int pl, int pr, const int l, const int r) {
    if (pl >= r || pr <= l) return Node();
    if (l <= pl && pr <= r) return tree[p];
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    return query(ls, pl, mid, l, r) + query(rs, mid, pr, l, r);
  }
};
struct Node {
  int data;
  Node() : data(2e9) {}
  Node(int data) : data(data) {}
  friend Node operator+(const Node& lhs, const Node& rhs) {
    return {min(lhs.data, rhs.data)};
  }
};
