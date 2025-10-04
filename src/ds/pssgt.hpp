template <typename Info>
struct SegTree {
  struct Node {
    Info info = {};
    int ls = -1, rs = -1;
  };
  int n, _pos, _l, _r;
  Info _v, _acc;
  vector<int> root;
  vector<Node> tree;
  SegTree(int n) : SegTree(vector<Info>(n)) {}
  SegTree(const vector<Info>& a) : n(a.size()) { root.PUSHB(build(0, n, a)); }
  void set(int p, int pos, Info f) {
    _pos = pos, _v = f, root.PUSHB(set_(p, 0, n));
  }
  Info sum(int p1, int p2, int l, int r) {
    return _l = l, _r = r, sum_(p1, p2, 0, n);
  }
  template <typename P>
  int bsearch(int p1, int p2, P pred) {
    return _acc = {}, bsearch_(p1, p2, 0, n, pred);
  }

 private:
#define MID (pl + (pr - pl) / 2)
  int new_(Node node) { return tree.PUSHB(move(node)), tree.size() - 1; }
  int pushup(int ls, int rs) {
    return new_(Node{tree[ls].info + tree[rs].info, ls, rs});
  }
  int build(int pl, int pr, const vector<Info>& a) {
    if (pr - pl == 1) return new_({a[pl], -1, -1});
    return pushup(build(pl, MID, a), build(MID, pr, a));
  }
  int set_(int p, int pl, int pr) {
    if (_pos < pl || pr <= _pos) return p;
    if (pr - pl == 1) return new_(Node{_v, -1, -1});
    return pushup(set_(tree[p].ls, pl, MID), set_(tree[p].rs, MID, pr));
  }
  Info sum_(int p1, int p2, int pl, int pr) {
    if (_r <= pl || pr <= _l) return {};
    if (_l <= pl && pr <= _r) return tree[p2].info - tree[p1].info;
    return sum_(tree[p1].ls, tree[p2].ls, pl, MID) +
           sum_(tree[p1].rs, tree[p2].rs, MID, pr);
  }
  template <typename P>
  int bsearch_(int p1, int p2, int pl, int pr, P pred) {
    if (pr - pl == 1)
      return pred(_acc + (tree[p2].info - tree[p1].info)) ? pr : pl;
    Info diff = tree[tree[p2].ls].info - tree[tree[p1].ls].info;
    if (pred(_acc + diff)) {
      _acc = _acc + diff;
      return bsearch_(tree[p1].rs, tree[p2].rs, MID, pr, pred);
    } else {
      return bsearch_(tree[p1].ls, tree[p2].ls, pl, MID, pred);
    }
  }
#undef MID
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
