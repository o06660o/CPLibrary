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
