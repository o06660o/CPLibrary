#define GC ch = getchar_unlocked()
ll read() {
  ll x = 0, f = 1, GC;
  while (ch < '0' || ch > '9') ch == '-' ? f = -1, GC : GC;
  while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', GC;
  return x * f;
}
#undef GC
