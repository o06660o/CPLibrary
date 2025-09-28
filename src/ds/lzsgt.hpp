template <typename Node, typename Tag, Node (*fn)(const Tag&, const Node&)>
struct SegTree {
  SegTree(int n) : n(n), tags(4 * n), tree(4 * n) {}
  SegTree(const vector<Node>& a) : SegTree(a.size()) { build(1, 0, n, a); }
  void apply(int l, int r, const Tag& f) { apply(1, 0, n, l, r, f); }
  Node query(int l, int r) { return query(1, 0, n, l, r); }

 private:
  int n;
  vector<Tag> tags;
  vector<Node> tree;
  void update(int p, const Tag& f) {
    tree[p] = fn(f, tree[p]);
    tags[p] = tags[p] + f;
  }
  void pushdown(int p) {
    int ls = p * 2, rs = p * 2 + 1;
    update(ls, tags[p]), update(rs, tags[p]);
    tags[p] = Tag();
  }
  void build(int p, int pl, int pr, const vector<Node>& a) {
    if (pr - pl == 1) return tree[p] = a[pl], void();
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    build(ls, pl, mid, a), build(rs, mid, pr, a);
    tree[p] = tree[ls] + tree[rs];
  }
  void apply(int p, int pl, int pr, const int l, const int r, const Tag& f) {
    if (pl >= r || pr <= l) return;
    if (l <= pl && pr <= r) return update(p, f);
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    pushdown(p);
    apply(ls, pl, mid, l, r, f), apply(rs, mid, pr, l, r, f);
    tree[p] = tree[ls] + tree[rs];
  }
  Node query(int p, int pl, int pr, const int l, const int r) {
    if (pl >= r || pr <= l) return Node();
    if (l <= pl && pr <= r) return tree[p];
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    pushdown(p);
    return query(ls, pl, mid, l, r) + query(rs, mid, pr, l, r);
  }
};
struct Node {
  ll sum;
  int len;
  Node() : sum(0), len(0) {}
  Node(ll sum, int len) : sum(sum), len(len) {}
  friend Node operator+(const Node& lhs, const Node& rhs) {
    return {lhs.sum + rhs.sum, lhs.len + rhs.len};
  }
};
struct Tag {
  ll add;
  Tag() : add(0) {}
  Tag(ll add) : add(add) {}
  friend Tag operator+(const Tag& lhs, const Tag& rhs) {
    return {lhs.add + rhs.add};
  }
};
Node fn(const Tag& f, const Node& x) {
  Node ret = x;
  ret.sum += x.len * f.add;
  return ret;
}
