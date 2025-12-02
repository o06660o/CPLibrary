## 数学

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
    a^m                                 & \text{ if } \gcd(a, m) \ne 1, n < \varphi(m) \\
    a^{n \bmod \varphi(m) + \varphi(m)} & \text{ if } \gcd(a, m) \ne 1, n \ge \varphi(m)
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
$m = \prod\limits_{i = 1}^n m_i, M_i = m / m_i$, 并且 $M_i^{-1}$ 是 $M_i$ 模 $m_i$ 意义下的逆元,
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

### 组合数的性质

$$
  \binom{n}{m} = \binom{n - 1}{m} + \binom{n - 1}{m - 1}
$$
$$
  \binom{n}{m} = \frac{n}{m}\binom{n - 1}{m - 1}
$$
$$
  \binom{n}{k} \binom{k}{m} = \binom{n}{m} \binom{n - m}{k - m}
$$

带权求和:
$$
  \sum_{i = 0}^n i \binom{n}{i} = n 2^{n - 1}
$$
$$
  \sum_{i = 0}^n i^2 \binom{n}{i} = n(n + 1) 2^{n - 2}
$$

Vandermonde 恒等式:
$$
  \sum_{i = 0}^k \binom{n}{i} \binom{m}{k - i} = \binom{n + m}{k}
$$

朱世杰恒等式:
$$
  \sum_{i = 0}^n \binom{i}{m} = \binom{n + 1}{m + 1}
$$

### 多重集的组合数

对于多重集 $S = \{n_1 \cdot a_1, n_2 \cdot a_2, \ldots, n_k \cdot a_k\}$,
记从 $S$ 中选出 $r \in \mathbb{N}^*$ 个元素组成一个多重集的方案数为 $C$.

如果 $r < n_i$ 恒成立, 使用插板法可知
$$
  C = \binom{r + k - 1}{k - 1}
$$

否则需要使用容斥原理, 全集是 $\sum\limits_{i = 1}^k x_i = r$ 的非负整数解,
$S_i$ 是满足 $x_i \le n$ 的解的集合, 那么有:
$$
  \begin{aligned}
    \left|\bigcup_{i = 1}^k \overline{S_i}\right|
     & =
    \sum_{i = 1}^k \left|\overline{S_i}\right| - \sum_{1 \le i_1 < i_2 \le k} \left|\overline{S_{i_1}} \cap
    \overline{S_{i_2}}\right| + \sum_{1 \le i_1 < i_2 < i_3 \le k} \left|\overline{S_{i_1}} \cap
    \overline{S_{i_2}} \cap \overline{S_{i_3}}\right| - \cdots + (-1)^{k - 1}
    \left|\bigcap_{i = 1}^k \overline{S_i}\right|                                     \\
     & = \sum_{i = 1}^k \binom{k + r - n_i - 2}{k - 1} - \sum_{1 \le i_1 < i_2 \le k}
    \binom{k + r - n_{i_1} - n_{i_2} - 3}{k - 1}                                      \\
     & + \sum_{1 \le i_1 < i_2 < i_3 \le k}
    \binom{k + r - n_{i_1} - n_{i_2} - n_{i_3} - 4}{k - 1} - \cdots + (-1)^{k - 1}
    \binom{k + r - \sum\limits_{i = 1}^k n_i - k - 1}{k - 1}
  \end{aligned}
$$
最后答案为
$$
  C = \left|U\right| - \left|\bigcup\limits_{i = 1}^k \overline{S_i}\right| =
  \sum_{p = 0}^k (-1)^p \sum_{\left|A\right| = p} \binom{k + r - \sum\limits_{i \in A}n_i - (p + 1)}{k - 1}
$$
实现就是二进制枚举子集 $A$.

### Catlan 数

$C_0 = C_1 = 1$, 当 $n \ge 2$ 时, 有
$$
  \begin{aligned}
    C_n & = \frac{1}{n + 1}\binom{2n}{n}
          = \prod_{i = 1}^n C_{i - 1} C_{n - i} \\
        & = \frac{4n - 2}{n + 1} C_{n - 1}
          = \binom{2n}{n} - \binom{2n}{n - 1}
  \end{aligned}
$$
常见组合意义: 由 $n$ 个 $+1$ 与 $n$ 个 $-1$ 组成的数列 $a_1, a_2, \ldots, a_{2n}$, 其部分和总是满足
$a_1 + a_2 + \cdots + a_k \ge 0 \quad (k = 1, 2, 3, \ldots, 2n)$ 的方案数为 $C_n$.

### 数论分块

对于形如
$$
  \sum\limits_{i = 1}^n f(i) g\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)
$$
的和式, 如果可以 $\mathcal{O}(1)$ 计算出 $f(i)$ 的区间和, 那么可以利用数论分块在
$\mathcal{O}(\sqrt{n})$ 的时间内完成计算.

核心思想是给定正整数 $n, l$, 如果令 $r = \left\lfloor \dfrac{n}{\lfloor n / l \rfloor}
\right\rfloor$, 那么 $\forall x \in [l, r]$, 有 $\left\lfloor\dfrac{n}{x}\right\rfloor$ 为定值.

下面是 $f(x) = 1, g(x) = x$ 时的特例.

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

### 大步小步算法

对于高次同余方程 $a^x \equiv b \pmod{p}$, 如果 $a, p$ 互质, 令 $t = \lceil \sqrt{p} \rceil$,
可以把 $x$ 改写为 $i \times t - j$, 其中 $0 \le i \le t, 0 \le j < t$. 方程变为
$(a^t)^i \equiv b \times a^j \pmod{p}$, 先枚举 $j$ 把右边结果插入哈希表, 再枚举 $i$
寻找是否有对应元素.

### 生成函数

普通生成函数 OGF 的形式为 $F(x) = \sum\limits_{n = 0}^{\infty}a_n x^n$, 指数生成函数 EGF 的形式为
$F(x) = \sum\limits_{n = 0}^{\infty}\dfrac{a_n}{x_n} x^n$.

应用:

从 $n$ 个球中选出若干个放入袋子 $1, 2, 3$, 要求袋子 $1$ 放入 $a$ 倍数个, 袋子 $2$ 放入 $b$ 倍数个,
袋子 $3$ 放入 $c$ 倍数个.

如果这 $n$ 个球全部相同, 那么方案数为多项式
$$
  G(x) =
  \left(\sum\limits_{n = 0}^{\infty}x^{na}\right)
  \times \left(\sum\limits_{n = 0}^{\infty}x^{nb}\right)
  \times \left(\sum\limits_{n = 0}^{\infty} x^{nc}\right)
$$
的第 $n$ 项.

如果这 $n$ 个球两两不同, 那么方案数为多项式
$$
  G(x) =
  \left(\sum\limits_{n = 0}^{\infty}\dfrac{1}{(na)!}x^{na}\right)
  \times \left(\sum\limits_{n = 0}^{\infty}\dfrac{1}{(nb)!}x^{nb}\right)
  \times \left(\sum\limits_{n = 0}^{\infty}\dfrac{1}{(nc)!}x^{nc}\right)
$$
的第 $n$ 项.

<!--
### 二项式变换

给定一个数列 $\{a_n\}$, 选取从 $a_s$ 开始的子列, 经过二项式变换后得到数列
$\{b_n\}$, 也可以从 $\{b_n\}$ 逆变换回 $\{a_n\}$.
$$
  b_n = \sum_{k = s}^{n} \binom{n}{k} a_k
  \Leftrightarrow
  a_n = \sum_{k = s}^{n} (-1)^{n - k} \binom{n}{k} b_k
$$

有 $n$ 个约束条件, 记 $f_m$ 为恰好满足 $m$ 条约束的方案数, $g_m$ 为至多满足 $m$ 条约束的方案数,
$h_m$ 为至少满足 $m$ 条约束的方案数.

若已知 $f_m$, 则有关系
$$
  g_m = \sum_{i = 0}^m \binom{m}{i} f_i
  \quad
  h_m = \sum_{i = m}^n \binom{i}{m} f_i
$$

反过来求 $f_m$ 可以利用
$$
  f_m = \sum_{i = 0}^m (-1)^{m - i} \binom{m}{i} g_i
  \quad
  f_m = \sum_{i = m}^n (-1)^{i - m} \binom{i}{m} h_i
$$
-->

### Z 变换

设全集 $X = \{1, 2, \ldots, n\}$, 对每个子集 $S \subseteq X$, 有一个值 $f(S)$. 如果 $g(S)$
是对所有子集求和的结果, $h(S)$ 是对所有超集求和的结果. 利用 $f(S)$ 可以 Z 变换得到 $g(S)$ 或者
$h(S)$, 也可以从 $g(S)$ 或者 $h(S)$ 逆变换回 $f(S)$. (逆变换也称为集合上的 Mobius 变换)

$$
  g(S) = \sum_{T \subseteq S} f(T)
  \Leftrightarrow
  f(S) = \sum_{T \subseteq S} (-1)^{\left|S\right| - \left|T\right|} g(T)
$$
$$
  h(S) = \sum_{T \supseteq S} f(T)
  \Leftrightarrow
  f(S) = \sum_{T \supseteq S} (-1)^{\left|T\right| - \left|S\right|} h(T)
$$

应用:

有 $n$ 个不同的约束条件对应全集, 记 $f(S)$ 为恰好只满足 $i \in S$ 的条件的方案数. 那么 $g(S)$
相当于只可能满足 $i \in S$ 的条件的方案数; $h(S)$ 相当于至少满足 $i \in S$ 的条件的方案数.

## 图论

### 基环树

```cpp
//  遍历基环树森林中的一棵树, 并标记出环.
//  - 时间复杂度 $\mathcal{O}(n)$.
//  - FIXME: 如果有自环, 那么这个环不会被标记 `vis[v] = 3`.
void cyctree() {
  int n;                     // Input.
  vector<vector<pii>> G(n);  // Input. First: to, second: edge id.
  vector<int> vis(n);        // Input.

  auto assign_vis = [&](auto&& self, int u, int fid) -> void {
    vis[u] = 1;
    for (auto [v, id] : G[u]) {
      if (id == fid) continue;
      if (vis[v] == 1) {
        vis[v] = 3;
        vis[u] = 2;
        continue;
      } else if (vis[v] == 2) {
        continue;
      }
      self(self, v, id);
      if (vis[v] == 2) {
        if (vis[v] != 3) vis[v] = 2;
      }
    }
  };
}
```

### 差分约束系统

对于约束条件 $x_i \le x_j + w$, 从 $j$ 到 $i$ 连权值为 $w$ 的边, 还需要建立超级源想每个点连权值为
$n$ 的边, 跑最短路, 存在负环则无解.

## 杂项

### 树上背包

有 $n$ 门课程, 第 $i$ 门课程的学分为 $a_i$, 每门课程有零门或一门先修课,
有先修课的课程需要先学完其先修课, 才能学习该课程. 一位学生要学习 $m$ 门课程, 求能获得的最大学分数.
这里定义 $f[u][i]$ 为从 $u$ 为根的树中选出 $i$ 门课程的最大得分, 时间复杂度 $\mathcal{O}(nm)$.

```cpp
#include <bits/stdc++.h>
#define PUSHB push_back
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  m++;
  vector<int> a(n + 1);
  vector<vector<int>> G(n + 1);
  for (int i = 0; i < n; i++) {
    int fa;
    cin >> fa >> a[i];
    fa--;
    if (fa == -1) {
      fa = n;
    }
    G[fa].PUSHB(i);
  }

  vector<int> siz(n + 1);
  vector<vector<int>> f(n + 1, vector<int>(m + 1));
  auto dfs = [&](auto&& self, int u) -> void {
    siz[u] = 1;
    f[u][1] = a[u];
    for (int v : G[u]) {
      self(self, v);
      for (int j = min(m, siz[u] + siz[v]); j >= 1; j--) {
        for (int k = max(1, j - siz[u]); k <= min(j - 1, siz[v]); k++) {
          f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
        }
      }
      siz[u] += siz[v];
    }
  };
  dfs(dfs, n);
  cout << f[n][m] << "\n";
  return 0;
}
```

### 主定理

如果有递推关系式
$$
  T(n) = aT\left(\frac{n}{b}\right) + f(n)
$$
其中 $a \ge 1, b > 1, n \in \mathbb{N}$, 那么
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

### 环境配置

```bash
setxkbmap -option caps:escape
touch _check
chmod +x _check
```

`~/.vimrc`:

```vim
colo slate
syn on
filet plugin indent on
se nocp nu hls is et sr sw=2 sts=2 cino+=:0,l1,L0 udf spr bo=all mouse=a
au TerminalOpen * se nonu
nn <C-s> :w<CR>
au BufNewFile *.cpp sil! 0r _vim_template.cpp | $d _
nn <Esc><C-n> :vert ter bash -c "
      \ulimit -s 1048576;
      \g++ -DDEBUG -std=c++17 -g %:r.cpp -o %:r
      \-fsanitize=address,undefined -Wall
      \&& ./%:r && cat main.out"<CR>
nn <Esc><CR> :vs main.in<CR>
nn <F5> :vert ter gdb %:r<CR>

" Some platform may need those.
se t_Co=256 bs=indent,col,start
lan en_US
```

`~/.gdbinit`:

```gdb
set debuginfo enabled off
```

`_vim_template.cpp`:

```cpp
#include <bits/stdc++.h>
#define ALL(a) (a).begin(), (a).end()
#define PUSHB push_back
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
#ifdef DEBUG
  freopen("main.in", "r", stdin);
  freopen("main.out", "w", stdout);
#endif
  return 0;
}
```

`_check`:

```bash
#!/bin/bash
g++ _generator.cpp -O2 -std=c++17 -o _generator
g++ main.cpp -O2 -std=c++17 -o main
g++ std.cpp -O2 -std=c++17 -o std
cnt=0
while true; do
  ./_generator >main.in
  ./main <main.in >main.out
  ./std <main.in >std.out
  # diff <(head -n 1 main.out) <(head -n 1 std.out)
  diff main.out std.out
  if [ $? -ne 0 ]; then break; fi
  cnt=$((cnt + 1))
  if [ $((cnt % 100)) -eq 0 ]; then
    cnt=0
    echo "ok 100 times"
  fi
done
```

`_check_spj`:

```bash
#!/bin/bash
g++ _generator.cpp -DSPJ -O2 -std=c++17 -o _generator
g++ main.cpp -DSPJ -O2 -std=c++17 -o main
g++ _spj.cpp -DSPJ -O2 -std=c++17 -o _spj
cnt=0
while true; do
  ./_generator >main.in
  ./main <main.in >main.out
  ./_spj <main.out || {
    echo "spj failed"
    break
  }
  cnt=$((cnt + 1))
  if [ $((cnt % 100)) -eq 0 ]; then
    cnt=0
    echo "ok 100 times"
  fi
done
```

## C++

- `std::cbrt()`: 传入 `double x`, 计算 $\sqrt[3]{x}$. (更高精度有 `std::cbrtl()`)
- `std::iota()`: `iota(arr.begin(), arr.end(), 0)`, 从 $0$ 开始填充整个 `arr`.
- `std::string`:
  - `std::to_string()`: 传入 `long long`, `long double` 之类的, 返回 `std::string()`.
  - `atoi()`, `std::stoi()`: 字符串转为整数, 前者是 `const char*` 后者是 `std::string`.
  更高精度有 `std::stoll()`.
  - `sscanf()`, `sprintf()`: 类似与 `scanf`, `printf`, 不过第一个参数是 `const char*`.
  - `std::getline(std::cin, buf)`: 从 `std::cin` 中读入一行内容放入 `buf`.
  - `.find()`: 查找某个 `char` 或者 `std::string`, 返回 `size_t`, 如果没找到返回 `string::npos`.
- `std::cout` 格式化输出
  - `std::fixed` 固定小数点, 不使用科学记数法.
  - `std::setprecision(n)`: 保留小数点后 $n$ 位.
  - `std::setw(n)` 指定最小宽度为 $n$, 默认右对齐, 填充空格.
  - `std::setfill(ch)`: 指定对齐时填充的字符.
  - `std::left`, `std::right`: 指定左对齐或右对齐.
  - `std::dec`, `std::hex`, `std::oct`: 以 10/16/8 进制 输出.
- `std::bitset` 的操作
  - `.count()`: 返回 `true` 的数量.
  - `.any()`; `.none()`; `.all()`: 是否存在某一个 `true`; 不存在 `true`; 全部是 `true`.
  - `.set()`; `.reset()`: 全部设为 `true`; 全部设为 `false`.
  - `.flip()`: 翻转每一位.
  - `.to_string()`; `.to_ulong()`; `.to_ullong()`: 类型转换.
  - `._Find_first()`; `._Find_next(pos)`: 返回第一个 `true` 的下标 (不存在返回 `size()`);
    返回下标严格大于 `pos` 的第一个 `true` 的下标 (不存在返回 `size()`).
- `sort()`, `unique()`, `erase()`, `next_permutation()`, `lower_bound()`, `upper_bound()`: 用法略.
