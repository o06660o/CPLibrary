// 2-SAT 问题: 给定 $n$ 个布尔变量, 与 $m$ 个形式为 $(x_i = f) \lor (x_j = g)$ 的条件.
// 如果有解答案构造在 `ans` 中.
#include "scc.hpp"
struct TwoSat {
  int n;
  vector<char> ans;
  SCC scc;
  TwoSat(int n) : n(n), ans(n), scc(2 * n) {}
  void adde(int i, bool f, int j, bool g) {
    scc.adde(2 * i + !f, 2 * j + g), scc.adde(2 * j + !g, 2 * i + f);
  }
  bool work() {
    scc.work();
    const auto& sccid = scc.sccid;
    for (int i = 0; i < n; i++) {
      if (sccid[2 * i] == sccid[2 * i + 1]) return false;
      ans[i] = sccid[2 * i] > sccid[2 * i + 1];
    }
    return true;
  }
};
