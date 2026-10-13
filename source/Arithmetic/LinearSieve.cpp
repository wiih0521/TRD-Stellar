// leastPrime[x], phi[x], mobius[x] for 1 <= x <= n in O(n).
struct LinearSieve {
    vector<int> primes, leastPrime, phi, mobius;

    LinearSieve(int n) : leastPrime(n + 1), phi(n + 1), mobius(n + 1) {
        if (n >= 1) phi[1] = mobius[1] = 1;
        for (int x = 2; x <= n; ++x) {
            if (!leastPrime[x]) {
                leastPrime[x] = x;
                phi[x] = x - 1;
                mobius[x] = -1;
                primes.push_back(x);
            }
            for (int p : primes) {
                if (p > leastPrime[x] || (ll)x * p > n) break;
                leastPrime[x * p] = p;
                if (x % p == 0) {
                    phi[x * p] = phi[x] * p;
                    mobius[x * p] = 0;
                } else {
                    phi[x * p] = phi[x] * (p - 1);
                    mobius[x * p] = -mobius[x];
                }
            }
        }
    }
};
