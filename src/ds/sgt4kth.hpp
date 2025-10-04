// 针对求区间第 k 小特化的可持久化权值线段树.
struct SegTree {
  struct Node {
    int sum = 0;
    int ls = -1, rs = -1;
  };
  int n, _pos, _l, _r;
  vector<int> root;
  vector<Node> tree;
  SegTree(int n) : n(n) { root.PUSHB(build(0, n)); }
  void add(int p, int pos) { _pos = pos, root.PUSHB(add(p, 0, n)); }
  int query(int p1, int p2, int l, int r, int kth) {
    return _l = l, _r = r, query_(p1, p2, 0, n, kth);
  }

 private:
#define mid (pl + (pr - pl) / 2)
  int new_(Node node) {
    tree.PUSHB(move(node));
    return tree.size() - 1;
  }
  int pushup(int ls, int rs) {
    return new_(Node{tree[ls].sum + tree[rs].sum, ls, rs});
  }
  int build(int pl, int pr) {
    if (pr - pl == 1) return new_(Node());
    return pushup(build(pl, mid), build(mid, pr));
  }
  int add(int p, int pl, int pr) {
    if (_pos < pl || pr <= _pos) return p;
    if (pr - pl == 1) return new_(Node{tree[p].sum + 1, -1, -1});
    return pushup(add(tree[p].ls, pl, mid), add(tree[p].rs, mid, pr));
  }
  int query_(int p1, int p2, int pl, int pr, int kth) {
    if (pr - pl == 1) return pl;
    int diff = tree[tree[p2].ls].sum - tree[tree[p1].ls].sum;
    return kth <= diff ? query_(tree[p1].ls, tree[p2].ls, pl, mid, kth)
                       : query_(tree[p1].rs, tree[p2].rs, mid, pr, kth - diff);
  }
#undef mid
};
