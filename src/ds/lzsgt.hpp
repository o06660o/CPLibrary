template <typename Node, typename Tag, void (*fn)(const Tag&, Node&)>
struct SegTree {
  int n, _l, _r;
  Tag _f;
  vector<Tag> tags;
  vector<Node> tree;
  SegTree(int n) : n(n), tags(4 * n), tree(4 * n) {}
  SegTree(const vector<Node>& a) : SegTree(a.size()) { build(1, 0, n, a); }
  void apply(int l, int r, Tag f) { _l = l, _r = r, _f = f, apply(1, 0, n); }
  Node query(int l, int r) { return _l = l, _r = r, query(1, 0, n); }

 private:
  void update(int p, const Tag& f) { fn(f, tree[p]), tags[p] += f; }
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
  void apply(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l) return;
    if (_l <= pl && pr <= _r) return update(p, _f);
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    pushdown(p), apply(ls, pl, mid), apply(rs, mid, pr);
    tree[p] = tree[ls] + tree[rs];
  }
  Node query(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l) return Node();
    if (_l <= pl && pr <= _r) return tree[p];
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    return pushdown(p), query(ls, pl, mid) + query(rs, mid, pr);
  }
};
struct Node {
  ll sum = 0;
  int len = 0;
  friend Node operator+(const Node& lhs, const Node& rhs) {
    return {lhs.sum + rhs.sum, lhs.len + rhs.len};
  }
};
struct Tag {
  ll add = 0;
  Tag operator+=(const Tag& rhs) {
    add += rhs.add;
    return *this;
  }
};
void fn(const Tag& f, Node& x) { x.sum += x.len * f.add; }
