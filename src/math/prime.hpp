vector<int> primes;
bitset<MAXN> isprime;
void init_prime_table() {
  isprime.set();
  isprime[0] = isprime[1] = false;
  for (int i = 2; i < MAXN; i++) {
    if (isprime[i]) primes.PUSHB(i);
    for (int p : primes) {
      if (i * p >= MAXN) break;
      isprime[i * p] = false;
      if (i % p == 0) break;
    }
  }
}
