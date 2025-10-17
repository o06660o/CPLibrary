// 针对扫描线特化的线段树, 支持区间覆盖, 撤销覆盖, 查询被覆盖的总长度.
struct SegTree {
  int n, _l, _r, _f;
  const vector<int>& _a;
  vector<int> len, sum, tag;
  SegTree(const vector<int>& a)
      : n(a.size()), _a(a), len(4 * n), sum(4 * n), tag(4 * n) {
    build(1, 0, n);
  }
  void apply(int l, int r, int f) { _l = l, _r = r, _f = f, apply_(1, 0, n); }

 private:
  void build(int p, int pl, int pr) {
    if (pr - pl == 1) return len[p] = _a[pl], void();
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    build(ls, pl, mid), build(rs, mid, pr);
    len[p] = len[ls] + len[rs];
  }
  void apply_(int p, int pl, int pr) {
    if (_r <= pl || pr <= _l) return;
    int ls = p * 2, rs = p * 2 + 1, mid = pl + (pr - pl) / 2;
    if (_l <= pl && pr <= _r) {
      sum[p] = (tag[p] += _f) ? len[p] : (pr - pl == 1 ? 0 : sum[ls] + sum[rs]);
      return;
    }
    apply_(ls, pl, mid), apply_(rs, mid, pr);
    sum[p] = tag[p] ? len[p] : sum[ls] + sum[rs];
  }
};
