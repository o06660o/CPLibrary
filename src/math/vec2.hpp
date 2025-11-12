constexpr double EPS = 1e-10;
struct Vec2 {
  double x, y;
  Vec2(double x = 0, double y = 0) : x(x), y(y) {}

  Vec2 operator-() const { return {-x, -y}; }
  Vec2& operator+=(const Vec2& rhs) { return x += rhs.x, y += rhs.y, *this; }
  Vec2& operator-=(const Vec2& rhs) { return x -= rhs.x, y -= rhs.y, *this; }
  Vec2& operator*=(double k) { return x *= k, y *= k, *this; }
  Vec2& operator/=(double k) { return x /= k, y /= k, *this; }
  friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) { return lhs += rhs; }
  friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) { return lhs -= rhs; }
  friend Vec2 operator*(Vec2 lhs, double k) { return lhs *= k; }
  friend Vec2 operator*(double k, Vec2 rhs) { return rhs *= k; }
  friend Vec2 operator/(Vec2 lhs, double k) { return lhs /= k; }
  friend double dot(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  friend double cross(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
  static int dcmp(double x) {
    if (abs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
  }
  friend bool operator==(const Vec2& lhs, const Vec2& rhs) {
    return dcmp(lhs.x - rhs.x) == 0 && dcmp(lhs.y - rhs.y) == 0;
  }
  friend bool operator<(const Vec2& lhs, const Vec2& rhs) {
    return tie(lhs.x, lhs.y) < tie(rhs.x, rhs.y);
  }
  double len_sq() const { return x * x + y * y; }
  double len() const { return sqrt(len_sq()); }
  Vec2 norm() const { return *this / len(); }
};
