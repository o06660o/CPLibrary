// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_queue
#include <bits/stdc++.h>
#define PUSHB push_back
using namespace std;
using ll = long long;

#include "../../src/ds/pssgt.hpp"
#include "../../src/misc/read.hpp"

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = read();
  vector<int> head(n + 1), tail(n + 1);
  SegTree<Info> sgt(n);
  for (int i = 1; i <= n; i++) {
    int op = read(), t = read();
    t++;
    if (op == 0) {
      int x = read();
      sgt.set(sgt.root[t], tail[t], Info{x});
      head[i] = head[t], tail[i] = tail[t] + 1;
    } else {
      auto qry = sgt.sum(sgt.root[0], sgt.root[t], head[t], head[t] + 1);
      cout << qry.data << "\n";
      sgt.set(sgt.root[t], head[t], Info{});
      head[i] = head[t] + 1, tail[i] = tail[t];
    }
  }
  return 0;
}
