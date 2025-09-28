ostream& operator<<(ostream& out, i128 x) {
  if (x == 0) {
    out << 0;
  } else if (x < 0) {
    out << "-", x = -x;
  }
  stack<int> S;
  while (x > 0) S.push(x % 10), x /= 10;
  while (!S.empty()) out << S.top(), S.pop();
  return out;
}
