template <typename Info>
struct SegTree {
  struct Node {
    Info info = {};
    int ls = -1, rs = -1;
  };
  int n, _pos, _l, _r, root;
  Info _v;
  vector<Node> tree;
  SegTree(int n) : n(n) { root = alloc({}); }
  SegTree(const vector<Info>& a) : n(a.size()) { root = build(0, n, a); }
  void set(int pos, Info v) { _pos = pos, _v = v, set(root, 0, n); }
  Info sum(int l, int r) { return _l = l, _r = r, sum(root, 0, n); }

 private:
  int alloc(Node node) { return tree.PUSHB(move(node)), int(tree.size()) - 1; }
  int build(int pl, int pr, const vector<Info>& a) {
    if (pr - pl == 1) return alloc({a[pl], -1, -1});
    int mid = (pl + pr) >> 1, ls = build(pl, mid, a), rs = build(mid, pr, a);
    return alloc({tree[ls].info + tree[rs].info, ls, rs});
  }
  void set(int p, int pl, int pr) {
    if (pr - pl == 1) return tree[p].info = _v, void();
    int mid = pl + (pr - pl) / 2, ls = tree[p].ls, rs = tree[p].rs;
    if (_pos < mid) {
      if (ls == -1) ls = tree[p].ls = alloc({});
      set(ls, pl, mid);
    } else {
      if (rs == -1) rs = tree[p].rs = alloc({});
      set(rs, mid, pr);
    }
    tree[p].info = tree[ls].info + tree[rs].info;
  }
  Info sum(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l || p == -1) return {};
    if (_l <= pl && pr <= _r) return tree[p].info;
    int mid = pl + (pr - pl) / 2, ls = tree[p].ls, rs = tree[p].rs;
    return sum(ls, pl, mid) + sum(rs, mid, pr);
  }
};
struct Info {
  int data = 2e9;
  friend Info operator+(const Info& lhs, const Info& rhs) {
    return {min(lhs.data, rhs.data)};
  }
};
