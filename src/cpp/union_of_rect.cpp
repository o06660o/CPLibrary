#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;
using ll = long long;

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

struct Line {
  int sign, x, y1, y2;
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  vector<Line> a(2 * n);
  vector<int> dc(2 * n);
  for (int i = 0; i < 2 * n; i += 2) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    a[i] = {1, x1, y1, y2}, a[i + 1] = {-1, x2, y1, y2};
    dc[i] = y1, dc[i + 1] = y2;
  }
  sort(ALL(dc)), dc.erase(unique(ALL(dc)), dc.end());
  map<int, int> mp;
  int N = dc.size();
  for (int i = 0; i < N; i++) {
    mp[dc[i]] = i;
  }
  sort(ALL(a), [](const Line& lhs, const Line& rhs) { return lhs.x < rhs.x; });
  for (auto& [_, __, y1, y2] : a) {
    y1 = mp[y1], y2 = mp[y2];
  }

  vector<int> init(N - 1);
  for (int i = 0; i < N - 1; i++) {
    init[i] = dc[i + 1] - dc[i];
  }
  SegTree sgt(init);

  ll ans = 0;
  sgt.apply(a[0].y1, a[0].y2, a[0].sign);
  for (int i = 1; i < 2 * n; i++) {
    ans += ll(sgt.sum[1]) * (a[i].x - a[i - 1].x);
    sgt.apply(a[i].y1, a[i].y2, a[i].sign);
  }
  cout << ans << "\n";
  return 0;
}
