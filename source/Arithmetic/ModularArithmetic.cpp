// Safe for 0 <= a,b < mod < 2^64 (requires GCC/Clang __int128).
using u64 = uint64_t;
using u128 = __uint128_t;

u64 modMul64(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 modPow64(u64 a, u64 e, u64 mod) {
    u64 result = 1 % mod;
    while (e) {
        if (e & 1) result = modMul64(result, a, mod);
        a = modMul64(a, a, mod);
        e >>= 1;
    }
    return result;
}

// Returns gcd(a,b), and x,y such that ax+by=gcd(a,b).
ll extGcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return abs(a);
    }
    ll x1, y1, g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Inverse modulo m, or -1 when gcd(a,m) != 1.
ll modInverse(ll a, ll m) {
    ll x, y;
    if (extGcd(a, m, x, y) != 1) return -1;
    return (x % m + m) % m;
}

// All inverses modulo a prime; requires 1 < n <= mod.
vector<ll> inverseTable(int n, ll mod) {
    vector<ll> inv(n);
    if (n > 1) inv[1] = 1;
    for (int i = 2; i < n; ++i)
        inv[i] = mod - mod / i * inv[mod % i] % mod;
    return inv;
}
