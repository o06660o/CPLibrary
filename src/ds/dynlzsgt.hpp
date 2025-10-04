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
  void set(int pos, Info v) { _pos = pos, _v = v, set(root, 0, n); }
  void apply(int l, int r, Tag f) { _l = l, _r = r, _f = f, apply(root, 0, n); }
  Info sum(int l, int r) { return _l = l, _r = r, sum(root, 0, n); }

 private:
  int alloc(Node node) { return tree.PUSHB(move(node)), int(tree.size()) - 1; }
  void update(int p, const Tag& f) { fn(tree[p].info, f), tree[p].tag += f; }
  void pushdown(int p) {
    update(tree[p].ls, tree[p].tag), update(tree[p].rs, tree[p].tag);
    tree[p].tag = {};
  }
  void set(int p, int pl, int pr) {
    if (pr - pl == 1) return tree[p].info = _v, tree[p].tag = {}, void();
    int ls = tree[p].ls, rs = tree[p].rs, mid = pl + (pr - pl) / 2;
    if (ls == -1) ls = tree[p].ls = alloc({});
    if (rs == -1) rs = tree[p].rs = alloc({});
    pushdown(p), _pos < mid ? set(ls, pl, mid) : set(rs, mid, pr);
    tree[p].info = tree[ls].info + tree[rs].info;
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
