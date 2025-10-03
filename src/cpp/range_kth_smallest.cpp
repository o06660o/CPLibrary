#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;

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

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<int> a(n), dc(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    dc[i] = a[i];
  }
  sort(ALL(dc)), dc.erase(unique(ALL(dc)), dc.end());
  int N = dc.size();
  map<int, int> mp;
  for (int i = 0; i < N; i++) {
    mp[dc[i]] = i;
  }
  for (auto& x : a) {
    x = mp[x];
  }
  SegTree sgt(N);
  for (int i = 0; i < n; i++) {
    sgt.add(sgt.root.back(), a[i]);
  }

  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    int qry = sgt.query(sgt.root[l], sgt.root[r], l, r, k + 1);
    cout << dc[qry] << "\n";
  }
  return 0;
}
