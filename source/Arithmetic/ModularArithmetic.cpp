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
