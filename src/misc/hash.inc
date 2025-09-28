struct Hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  inline static const uint64_t FIXED_RANDOM =
      chrono::steady_clock::now().time_since_epoch().count();
  size_t operator()(uint64_t x) const { return splitmix64(x + FIXED_RANDOM); }
  size_t operator()(pair<uint64_t, uint64_t> x) const {
    return splitmix64(x.first + FIXED_RANDOM) ^
           (splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
  size_t operator()(array<uint64_t, 2> x) const {
    return splitmix64(x[0] + FIXED_RANDOM) ^
           (splitmix64(x[1] + FIXED_RANDOM) >> 1);
  }
};
