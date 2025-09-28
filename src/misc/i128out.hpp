ostream& operator<<(ostream& out, i128 x) {
  if (x == 0) return out.put('0');
  if (x < 0) out.put('-'), x = -x;
  static char buf[40];
  int ptr = 40;
  while (x) buf[--ptr] = '0' + x % 10, x /= 10;
  return out.write(buf + ptr, 40 - ptr);
}
