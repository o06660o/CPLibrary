i128 gcd(i128 a, i128 b) {
  while (b != 0) {
    i128 t = b;
    b = a % b;
    a = t;
  }
  return a;
}
i128 lcm(i128 a, i128 b) { return a / gcd(a, b) * b; }
