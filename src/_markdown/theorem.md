## 主定理

如果有递推关系式
$$
  T(n) = aT\left(\frac{n}{b}\right) + f(n)
$$
其中 $a \ge 1, \, b > 1, \, n \in \mathbb{N}$, 那么
$$
  T(n) = \begin{cases}
    \Theta(n^{\log_b a})              & \text{if } f(n) = \mathcal{O}(n^{\log_b a - \varepsilon})
    \text{ for some } \varepsilon > 0                                                             \\
    \Theta(n^{\log_b a}\log^{k + 1}n) & \text{if } f(n) = \Theta(n^{\log_b a}\log^k n)
    \text{ for some } k \ge 0                                                                     \\
    \Theta(f(n))                      & \text{if } f(n) = \Omega(n^{\log_b a + \varepsilon})
    \text{ for some } \varepsilon > 0
  \end{cases}
$$
其中最后一条还要求对于某个常数 $c < 1$ 以及所有充分大的 $n$, 有 $a f(n / b) \le c f(n)$.

## 数学

### 数论

#### 数论分块

对于形如
$$
  \sum\limits_{i = 1}^n f(i) g\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)
$$
的和式, 如果可以 $\mathcal{O}(1)$ 计算出 $f(i)$ 的区间和, 那么可以利用数论分块在
$\mathcal{O}(\sqrt{n})$ 的时间内完成计算.

核心思想是给定正整数 $n, \, l$, 如果令 $r = \left\lfloor \dfrac{n}{\lfloor n / l \rfloor}
\right\rfloor$, 那么 $\forall x \in [l, r]$, 有 $\left\lfloor\dfrac{n}{x}\right\rfloor$ 为定值.

下面是 $f(x) = 1, \, g(x) = x$ 时的特例.

```cpp
i128 floor_sum(ll n) {
  i128 ret = 0;
  for (ll l = 1, r; l <= n; l = r) {
    r = n / (n / l) + 1;
    ret += (r - l) * (n / l);
  }
  return ret;
}
```

