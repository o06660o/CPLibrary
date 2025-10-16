vector<int> primes;
bitset<MAXN> is_prime;
void init_prime_table() {
  is_prime.set();
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i < MAXN; i++) {
    if (is_prime[i]) primes.push_back(i);
    for (int p : primes) {
      if (i * p >= MAXN) break;
      is_prime[i * p] = false;
      if (i % p == 0) break;
    }
  }
}
