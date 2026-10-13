// All operations are modulo mod; mod must be prime.
// berlekampMassey(s): finds the shortest recurrence
//   s[i] = sum(rec[j] * s[i - j - 1]).
// linearRec(init, rec, k): returns the 0-indexed k-th term.
// Complexity: O(N^2) and O(L^2 log k), respectively.

using ll = long long;
const ll mod = 998244353;

ll modpow(ll a, ll e) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

vector<ll> berlekampMassey(vector<ll> s) {
    int n = (int)s.size(), L = 0, m = 0;
    if (n == 0) return {};
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;

    ll b = 1;
    for (int i = 0; i < n; ++i) {
        ++m;
        ll d = (s[i] % mod + mod) % mod;
        for (int j = 1; j <= L; ++j)
            d = (d + C[j] * s[i - j]) % mod;
        if (d == 0) continue;

        T = C;
        ll coef = d * modpow(b, mod - 2) % mod;
        for (int j = m; j < n; ++j)
            C[j] = (C[j] - coef * B[j - m]) % mod;
        if (2 * L > i) continue;

        L = i + 1 - L;
        B = T;
        b = d;
        m = 0;
    }

    C.resize(L + 1);
    C.erase(C.begin());
    for (ll& x : C) x = (mod - x) % mod;
    return C;
}

ll linearRec(vector<ll> init, vector<ll> rec, long long k) {
    int n = (int)rec.size();
    if (k < (long long)init.size()) return (init[k] % mod + mod) % mod;
    if (n == 0) return 0;
    assert((int)init.size() >= n);

    auto combine = [&](vector<ll> a, vector<ll> b) {
        vector<ll> res(2 * n + 1);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                res[i + j] = (res[i + j] + a[i] * b[j]) % mod;

        for (int i = 2 * n; i > n; --i)
            for (int j = 0; j < n; ++j)
                res[i - 1 - j] =
                    (res[i - 1 - j] + res[i] * rec[j]) % mod;
        res.resize(n + 1);
        return res;
    };

    vector<ll> pol(n + 1), e(n + 1);
    pol[0] = e[1] = 1;
    for (++k; k > 0; k >>= 1) {
        if (k & 1) pol = combine(pol, e);
        e = combine(e, e);
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i)
        ans = (ans + pol[i + 1] * init[i]) % mod;
    return ans;
}
