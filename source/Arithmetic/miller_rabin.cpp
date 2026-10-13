namespace MillerRabin {
using u64 = uint64_t;
using u128 = __uint128_t;

u64 multiply(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 power(u64 base, u64 exponent, u64 mod) {
    u64 result = 1;
    while (exponent) {
        if (exponent & 1) result = multiply(result, base, mod);
        base = multiply(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

// Deterministic for every unsigned 64-bit integer.
bool isPrime64(u64 n) {
    if (n < 2) return false;
    for (u64 prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL,
                      19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
        if (n % prime == 0) return n == prime;
    int shifts = 0;
    u64 odd = n - 1;
    while (!(odd & 1)) odd >>= 1, ++shifts;
    for (u64 base : {2ULL, 325ULL, 9375ULL, 28178ULL,
                     450775ULL, 9780504ULL, 1795265022ULL}) {
        if (base % n == 0) continue;
        u64 value = power(base % n, odd, n);
        if (value == 1 || value == n - 1) continue;
        bool composite = true;
        for (int round = 1; round < shifts; ++round) {
            value = multiply(value, value, n);
            if (value == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
}
