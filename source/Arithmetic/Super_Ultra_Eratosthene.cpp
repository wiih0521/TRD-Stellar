
/* LOOK AT THIS DUDE! THIS SHIT IS 15 TIME FASTER THAN ORDINARY SIEVE. */
/* IT IS THE MOST CONCISE VERSION. IT IS TOO COMPLICATED */
/* 
 * Usage : 
 * isPrime() : function checks primality using Miller-Rabin.
 * calculatePhi() : function computes the Euler's Totient Function for a range of values.
 * euclid() : Computes the greatest common divisor (GCD) of two numbers using the 
 extended Euclidean algorithm, also returning the coefficients for Bézout’s identity.
 * update_sieve() : function marks non-prime numbers in the current segment.
 * sieve() : Uses the segmented sieve to compute all primes up to MAX, 
 with wheel factorization to skip certain multiples and reduce computation.
 */

typedef unsigned long long ull;
typedef long long ll;

const int LIM = 5000000;
const int MAX = 1000000000LL, WHEEL = 3 * 5 * 7 * 11 * 13, SIEVE_SPAN = WHEEL * 64;
const int N_SMALL_PRIMES = 6536;
uint64_t ONES[64], si[SIEVE_SPAN / 128 + 1], pattern[WHEEL];
int phi[LIM], small_primes[N_SMALL_PRIMES];

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
    for (ull a : A) {
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

void calculatePhi() {
    for (int i = 0; i < LIM; ++i) phi[i] = i & 1 ? i : i / 2;
    for (int i = 3; i < LIM; i += 2) if (phi[i] == i)
        for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}

ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}

inline void mark(uint64_t *s, int o) { s[o >> 6] |= ONES[o & 63]; }
inline int test(uint64_t *s, int o) { return (s[o >> 6] & ONES[o & 63]) == 0; }

void update_sieve(int offset) {
    for (int i = 0, k; i < SIEVE_SPAN / 128 + 1; i += k) {
        k = min(WHEEL, SIEVE_SPAN / 128 + 1 - i);
        memcpy(si + i, pattern, sizeof(*pattern) * k);
    }
    if (offset == 0) si[0] |= ONES[0], si[0] &= ~(ONES[1] | ONES[2] | ONES[3] | ONES[5] | ONES[6]);
    for (int i = 0; i < N_SMALL_PRIMES; ++i) {
        int j = small_primes[i] * small_primes[i];
        if (j > offset + SIEVE_SPAN - 1) break;
        if (j > offset) j = (j - offset) >> 1;
        else { j = small_primes[i] - offset % small_primes[i]; if ((j & 1) == 0) j += small_primes[i]; j >>= 1; }
        while (j < SIEVE_SPAN / 2) mark(si, j), j += small_primes[i];
    }
}

void sieve() {
    for (int i = 0; i < 64; ++i) ONES[i] = 1ULL << i;
    for (int i = 3; i < 256; i += 2) if (test(si, i >> 1)) 
        for (int j = i * i / 2; j < 32768; j += i) mark(si, j);
    for (int i = 8, m = 0; i < 32768; ++i) if (test(si, i)) small_primes[m++] = i * 2 + 1;
    for (int i = 1; i < WHEEL * 64; i += 3) mark(pattern, i);
    for (int i = 2; i < WHEEL * 64; i += 5) mark(pattern, i);
    for (int i = 3; i < WHEEL * 64; i += 7) mark(pattern, i);
    for (int i = 5; i < WHEEL * 64; i += 11) mark(pattern, i);
    for (int i = 6; i < WHEEL * 64; i += 13) mark(pattern, i);
    
    long long sum_primes = 2;
    for (int offset = 0; offset < MAX; offset += SIEVE_SPAN) {
        update_sieve(offset);
        for (uint32_t j = 0; j < SIEVE_SPAN / 128 + 1; ++j) {
            uint64_t x = ~si[j];
            while (x) {
                uint32_t p = offset + (j << 7) + (__builtin_ctzll(x) << 1) + 1;
                if (p > offset + SIEVE_SPAN - 1) break;
                if (p <= MAX) sum_primes += p;
                x ^= (-x & x);
            }
        }
    }
    assert(sum_primes == SUM_PRIMES);
    return;
}