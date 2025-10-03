template <typename Info, typename Tag, void (*fn)(Info&, const Tag&)>
struct SegTree {
  int n, _l, _r;
  Tag _f;
  vector<Tag> tags;
  vector<Info> tree;
  SegTree(int n) : n(n), tags(4 * n), tree(4 * n) {}
  SegTree(const vector<Info>& a) : SegTree(a.size()) { build(1, 0, n, a); }
  void apply(int l, int r, Tag f) { _l = l, _r = r, _f = f, apply(1, 0, n); }
  Info sum(int l, int r) { return _l = l, _r = r, sum(1, 0, n); }

 private:
  void update(int p, const Tag& f) { fn(tree[p], f), tags[p] += f; }
  void pushdown(int p) {
    int ls = p * 2, rs = p * 2 + 1;
    update(ls, tags[p]), update(rs, tags[p]), tags[p] = {};
  }
  void build(int p, int pl, int pr, const vector<Info>& a) {
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
  Info sum(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l) return {};
    if (_l <= pl && pr <= _r) return tree[p];
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    return pushdown(p), sum(ls, pl, mid) + sum(rs, mid, pr);
  }
};
struct Info {
  ll sum = 0;
  int len = 0;
  friend Info operator+(const Info& lhs, const Info& rhs) {
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
void fn(Info& x, const Tag& f) { x.sum += x.len * f.add; }
