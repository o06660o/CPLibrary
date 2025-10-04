template <typename Info>
struct SegTree {
  struct Node {
    Info info = {};
    int ls = -1, rs = -1;
  };
  int n, _pos, _l, _r;
  Info _v;
  vector<int> root;
  vector<Node> tree;
  SegTree(int n) : n(n) { root.PUSHB(build(0, n)); }
  void set(int p, int pos, Info f) {
    _pos = pos, _v = f, root.PUSHB(set(p, 0, n));
  }
  Info sum(int p1, int p2, int l, int r) {
    return _l = l, _r = r, sum_(p1, p2, 0, n);
  }

 private:
#define mid (pl + (pr - pl) / 2)
  int new_(Node node) { return tree.PUSHB(move(node)), tree.size() - 1; }
  int pushup(int ls, int rs) {
    return new_(Node{tree[ls].info + tree[rs].info, ls, rs});
  }
  int build(int pl, int pr) {
    if (pr - pl == 1) return new_({});
    return pushup(build(pl, mid), build(mid, pr));
  }
  int set(int p, int pl, int pr) {
    if (_pos < pl || pr <= _pos) return p;
    if (pr - pl == 1) return new_(Node{_v, -1, -1});
    return pushup(set(tree[p].ls, pl, mid), set(tree[p].rs, mid, pr));
  }
  Info sum_(int p1, int p2, int pl, int pr) {
    if (_r <= pl || pr <= _l) return {};
    if (_l <= pl && pr <= _r) return tree[p2].info - tree[p1].info;
    return sum_(tree[p1].ls, tree[p2].ls, pl, mid) +
           sum_(tree[p1].rs, tree[p2].rs, mid, pr);
  }
#undef mid
};
struct Info {
  int data = 0;
  friend Info operator+(const Info& lhs, const Info& rhs) {
    return {lhs.data + rhs.data};
  }
  friend Info operator-(const Info& lhs, const Info& rhs) {
    return {lhs.data - rhs.data};
  }
};
