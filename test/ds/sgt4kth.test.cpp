// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;

#include "../../src/ds/sgt4kth.hpp"

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
