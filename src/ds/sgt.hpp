template <typename Info>
struct SegTree {
  int n, _pos, _l, _r;
  Info _node;
  vector<Info> tree;
  SegTree(int n) : n(n), tree(4 * n) {}
  SegTree(const vector<Info>& a) : SegTree(a.size()) { build(1, 0, n, a); }
  void set(int pos, Info node) { _pos = pos, _node = node, set(1, 0, n); }
  Info sum(int l, int r) { return _l = l, _r = r, sum(1, 0, n); }

 private:
  void build(int p, int pl, int pr, const vector<Info>& a) {
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
  Info sum(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l) return {};
    if (_l <= pl && pr <= _r) return tree[p];
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    return sum(ls, pl, mid) + sum(rs, mid, pr);
  }
};
struct Info {
  int data = 2e9;
  friend Info operator+(const Info& lhs, const Info& rhs) {
    return {min(lhs.data, rhs.data)};
  }
};
