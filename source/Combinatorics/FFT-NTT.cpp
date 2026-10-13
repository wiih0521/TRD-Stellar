// NTT convolution modulo 998244353. Inputs must be normalized modulo MOD.
namespace NTT {
    using ll = long long;
    const ll MOD = 998244353, ROOT = 3;

    ll power(ll a, ll e) {
        ll result = 1;
        while (e) {
            if (e & 1) result = result * a % MOD;
            a = a * a % MOD; e >>= 1;
        }
        return result;
    }
    void transform(vector<ll>& a, bool inverse) {
        int n = (int)a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            while (j & bit) j ^= bit, bit >>= 1;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            ll root = power(ROOT, (MOD - 1) / len);
            if (inverse) root = power(root, MOD - 2);
            for (int i = 0; i < n; i += len) {
                ll w = 1;
                for (int j = 0; j < len / 2; ++j) {
                    ll u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + len / 2] = (u - v + MOD) % MOD;
                    w = w * root % MOD;
                }
            }
        }
        if (inverse) {
            ll invN = power(n, MOD - 2);
            for (ll& x : a) x = x * invN % MOD;
        }
    }
    vector<ll> convolution(vector<ll> a, vector<ll> b) {
        if (a.empty() || b.empty()) return {};
        int need = (int)a.size() + (int)b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        a.resize(n); b.resize(n);
        transform(a, false); transform(b, false);
        for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % MOD;
        transform(a, true); a.resize(need);
        return a;
    }
}
