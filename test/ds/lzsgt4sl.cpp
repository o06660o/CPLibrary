// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/area_of_union_of_rectangles
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;
using ll = long long;

#include "../../src/ds/lzsgt4sl.hpp"
#include "../../src/misc/read.hpp"

struct Line {
  int sign, x, y1, y2;
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read();
  vector<Line> a(2 * n);
  vector<int> dc(2 * n);
  for (int i = 0; i < 2 * n; i += 2) {
    int x1 = read(), y1 = read(), x2 = read(), y2 = read();
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
