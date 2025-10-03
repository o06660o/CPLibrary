template <typename Info, typename Tag, void (*fn)(Info&, const Tag&)>
struct SegTree {
  struct Node {
    Info info = {};
    Tag tag = {};
    int ls = -1, rs = -1;
  };
  int n, _pos, _l, _r, root;
  Info _v;
  Tag _f;
  vector<Node> tree;
  SegTree(int n) : n(n) { root = alloc({}); }
  SegTree(const vector<Info>& a) : n(a.size()) { root = build(0, n, a); }
  void apply(int l, int r, Tag f) { _l = l, _r = r, _f = f, apply(root, 0, n); }
  Info sum(int l, int r) { return _l = l, _r = r, sum(root, 0, n); }

 private:
  int alloc(Node node) { return tree.PUSHB(move(node)), int(tree.size()) - 1; }
  void update(int p, const Tag& f) { fn(tree[p].info, f), tree[p].tag += f; }
  void pushdown(int p) {
    update(tree[p].ls, tree[p].tag), update(tree[p].rs, tree[p].tag);
    tree[p].tag = {};
  }
  int build(int pl, int pr, const vector<Info>& a) {
    if (pr - pl == 1) return alloc({a[pl], {}, -1, -1});
    int mid = (pl + pr) >> 1, ls = build(pl, mid, a), rs = build(mid, pr, a);
    return alloc({tree[ls].info + tree[rs].info, {}, ls, rs});
  }
  void apply(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l || p == -1) return;
    if (_l <= pl && pr <= _r) return update(p, _f);
    int ls = tree[p].ls, rs = tree[p].rs, mid = pl + (pr - pl) / 2;
    if (ls == -1) ls = tree[p].ls = alloc({});
    if (rs == -1) rs = tree[p].rs = alloc({});
    pushdown(p), apply(ls, pl, mid), apply(rs, mid, pr);
    tree[p].info = tree[ls].info + tree[rs].info;
  }
  Info sum(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l || p == -1) return {};
    if (_l <= pl && pr <= _r) return tree[p].info;
    int ls = tree[p].ls, rs = tree[p].rs, mid = pl + (pr - pl) / 2;
    if (ls == -1) ls = tree[p].ls = alloc({});
    if (rs == -1) rs = tree[p].rs = alloc({});
    return pushdown(p), sum(ls, pl, mid) + sum(rs, mid, pr);
  }
};
