// 插入元素时间复杂度 $\mathcal{O}(L)$. 基底各数字二进制最高位不同.
template <int L>
struct XorBasis {
  array<bitset<L>, L> data;
  bool insert(bitset<L> x) {
    for (int i = L - 1; i >= 0; i--) {
      if (!x[i]) continue;
      if (data[i].none()) return data[i] = x, true;
      x ^= data[i];
    }
    return false;
  }
  friend XorBasis operator&(XorBasis lhs, const XorBasis& rhs) {
    XorBasis ret;
    array<bitset<L>, L> buf{};
    for (int i = L - 1; i >= 0; i--) {
      auto x = rhs.data[i], y = x;
      for (int k = i; k >= 0 && x.any(); k--) {
        if (!x[k]) continue;
        if (lhs.data[k].none()) lhs.data[k] = x, buf[k] = y;
        x ^= lhs.data[k], y ^= buf[k];
      }
      ret.insert(y);
    }
    return ret;
  }
};
