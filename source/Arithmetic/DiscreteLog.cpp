// Smallest x > 0 with a^x == b (mod m), or -1. Works when gcd(a,m) > 1.
// O(sqrt(m)) expected time and memory.
ll discreteLog(ll a, ll b, ll m) {
    if (m == 1) return 1;
    a %= m;
    b = (b % m + m) % m;
    ll n = (ll)sqrt((long double)m) + 1;
    ll e = 1 % m, step = 1 % m, j = 1;
    unordered_map<ll, ll> baby;
    while (j <= n && (e = step = (__int128)e * a % m) != b)
        baby[(__int128)e * b % m] = j++;
    if (e == b) return j;
    if (gcd(m, e) == gcd(m, b)) {
        for (ll i = 2; i <= n + 1; ++i) {
            e = (__int128)e * step % m;
            auto it = baby.find(e);
            if (it != baby.end()) return n * i - it->second;
        }
    }
    return -1;
}
