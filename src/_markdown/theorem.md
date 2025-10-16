## 公式

### 主定理

如果有递推关系式
$$
  T(n) = aT\left(\frac{n}{b}\right) + f(n)
$$
其中 $a \ge 1, \, b > 1, \, n \in \mathbb{N}$, 那么
$$
  T(n) = \begin{cases}
    \Theta(n^{\log_b a})              & \text{ if } f(n) = \mathcal{O}(n^{\log_b a - \varepsilon})
    \text{ for some } \varepsilon > 0                                                             \\
    \Theta(n^{\log_b a}\log^{k + 1}n) & \text{ if } f(n) = \Theta(n^{\log_b a}\log^k n)
    \text{ for some } k \ge 0                                                                     \\
    \Theta(f(n))                      & \text{ if } f(n) = \Omega(n^{\log_b a + \varepsilon})
    \text{ for some } \varepsilon > 0
  \end{cases}
$$
其中最后一条还要求对于某个常数 $c < 1$ 以及所有充分大的 $n$, 有 $a f(n / b) \le c f(n)$.

### 数论分块

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

### Fermat 小定理

给定质数 $p$, 对于任意整数 $a$, 有
$$
  a^p \equiv a \pmod{p}
$$

### 扩展 Euler 定理

对于任意整数 $a$, 正整数 $m$, 和非负整数 $n$, 有
$$
  a^n \equiv \begin{cases}
    a^{n \bmod \varphi(m)}              & \text{ if } \gcd(a, m) = 1 \\
    a^m                                 & \text{ if } \gcd(a, m) \ne 1, \, n < \varphi(m) \\
    a^{n \bmod \varphi(m) + \varphi(m)} & \text{ if } \gcd(a, m) \ne 1, \, n \ge \varphi(m)
  \end{cases} \pmod{m}
$$

### Lucas 定理

对于素数 $p$, 有
$$
  \binom{n}{m} \equiv \binom{\lfloor n / p \rfloor}{\lfloor m / p \rfloor}
  \binom{n \bmod p}{m \bmod p} \pmod{p}
$$

```cpp
int lucas(ll n, ll m, int p) {
  if (m == 0) return 1;
  return ll(binom(n % p, m % p, p)) * lucas(n / p, m / p, p) % p;
}
```

### 中国剩余定理

给定若干线性同余方程 $x \equiv a_i \pmod{m_i}$, 如果模数两两互质, 那么令
$m = \prod\limits_{i = 1}^n m_i, \, M_i = m / m_i$, 并且 $M_i^{-1}$ 是 $M_i$ 模 $m_i$ 意义下的逆元,
那么方程组有整数解, 解为 $x \equiv \sum\limits_{i = 1}^n a_i M_i M_i^{-1} \pmod{m}$.

```cpp
pll crt(const vector<int>& a, const vector<int>& p) {
  assert(a.size() == p.size());
  ll x = 0, m = 1;
  for (int x : p) m *= x;
  for (int i = 0; i < int(a.size()); i++) {
    ll M = m / p[i], inv = getinv(M, p[i]);
    x = (x + i128(a[i]) * M * inv % m) % m;
  }
  return {x, m};
}
```

### 扩展中国剩余定理

考虑两个模数不互质的线性同余方程. 第一个方程的解形如 $x = a_1 + k_1 m_1$,
那么第二个方程要存在一个整数 $t$, 满足 $a_1 + t m_1 \equiv a_2 \pmod{m_2}$,
等价于 $t m_1 \equiv a_2 - a_1 \pmod{m_2}$, 这是一个关于变量 $t$ 的线性同余方程.

如果 $a_2 - a_1$ 不能被 $\gcd(m_1, m_2)$ 整除, 那么方程无解.

否则解出一个 $t$, 两个方程的解为 $x^* \equiv t m_1 + a_1 \pmod{\lcm(m_1, m_2)}$.

对于多个模数不互质的线性同余方程, 可以利用上面的方法合并前 $k$ 个方程组与第 $k + 1$
个方程.

```cpp
pll excrt(const vector<int>& a, const vector<int>& m) {
  assert(a.size() == m.size());
  ll x = a[0] % m[0], M = m[0];
  for (int i = 1; i < int(a.size()); i++) {
    ll r1, r2, g = exgcd(M, m[i], r1, r2);
    if ((a[i] - x) % g != 0) return {-1, -1};
    i128 k1 = i128(a[i] - x) / g * r1;
    i128 tmp = x + k1 * M;
    M = lcm(M, m[i]);
    x = (tmp % M + M) % M;
  }
  return {x, M};
}
```

### 大步小步算法

对于高次同余方程 $a^x \equiv b \pmod{p}$, 如果 $a, p$ 互质, 令 $t = \lceil \sqrt{p} \rceil$,
可以把 $x$ 改写为 $i \times t - j$, 其中 $0 \le i \le t, \, 0 \le j < t$. 方程变为
$(a^t)^i \equiv b \times a^j \pmod{p}$, 先枚举 $j$ 把右边结果插入哈希表, 再枚举 $i$
寻找是否有对应元素.
