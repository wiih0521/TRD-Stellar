
using ll = long long;
using C = complex<double>;
constexpr ll MOD = 998244353;
static inline ll modpow(ll x, ll e) {
    ll r = 1 % MOD;
    while (e) {
        if (e & 1) r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return r;

}

static inline ll invmod(ll x) { return modpow(x, MOD - 2); }
struct Poly {
    vector<ll> a;
    Poly(vector<ll> v = vector<ll>(0)) : a(v) {}
    // ---------- FFT (for convolution) ----------

    static void fft(vector<C> &f) {
        int n = (int)f.size(), L = 31 - __builtin_clz(n);
        static vector<complex<long double>> R(2, 1);
        static vector<C> rt(2, 1);
        for (int k = 2; k < n; k <<= 1) {
            R.resize(n); rt.resize(n);
            auto x = polar(1.0L, acosl(-1.0L) / k);
            for (int i = k; i < 2 * k; ++i) rt[i] = R[i] = (i & 1) ? R[i/2] * x : R[i/2];
        }
        vector<int> rev(n);
        for (int i = 0; i < n; ++i) rev[i] = (rev[i/2] | (i & 1) << L) / 2;
        for (int i = 0; i < n; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0; i < n; i += k << 1)
                for (int j = 0; j < k; ++j) {
                    auto x = (double*)&rt[j+k], y = (double*)&f[i+j+k];
                    C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
                    f[i+j+k] = f[i+j] - z;
                    f[i+j] += z;
                }
    }
    // convolution using FFT-splitting trick (handles large MOD)
    static vector<ll> conv(const vector<ll>& A, const vector<ll>& B) {
        if (A.empty() || B.empty()) return {};
        int need = (int)A.size() + (int)B.size() - 1;
        int B2 = 32 - __builtin_clz(need), n = 1 << B2;
        int cut = (int)floor(sqrt(MOD));
        vector<C> L(n), R(n);
        for (size_t i = 0; i < A.size(); ++i) L[i] = C((ll)(A[i] / cut), (ll)(A[i] % cut));
        for (size_t i = 0; i < B.size(); ++i) R[i] = C((ll)(B[i] / cut), (ll)(B[i] % cut));
        fft(L); fft(R);
        vector<C> outl(n), outs(n);
        for (int i = 0; i < n; ++i) {
            int j = (-i) & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / C(0,1);
        }
        fft(outl); fft(outs);
        vector<ll> res(need);
        for (int i = 0; i < need; ++i) {
            ll av = (ll) (real(outl[i]) + 0.5) % MOD;
            ll cv = (ll) (imag(outs[i]) + 0.5) % MOD;
            ll bv = ((ll)(imag(outl[i]) + 0.5) + (ll)(real(outs[i]) + 0.5)) % MOD;
            res[i] = (( (av * cut + bv) % MOD) * cut + cv) % MOD;
        }
        return res;

    }

    // ---------- operators ----------
    Poly operator+(const Poly& o) const {
        vector<ll> r(max(a.size(), o.a.size()), 0);
        for (size_t i = 0; i < r.size(); ++i) {
            ll x = i < a.size() ? a[i] : 0;
            ll y = i < o.a.size() ? o.a[i] : 0;
            r[i] = (x + y) % MOD;
        }
        return Poly(r);
    }
    Poly operator-(const Poly& o) const {
        vector<ll> r(max(a.size(), o.a.size()), 0);
        for (size_t i = 0; i < r.size(); ++i) {
            ll x = i < a.size() ? a[i] : 0;
            ll y = i < o.a.size() ? o.a[i] : 0;
            r[i] = (x - y) % MOD;
            if (r[i] < 0) r[i] += MOD;
        }
        return Poly(r);
    }
    Poly operator*(const Poly& o) const {
        return Poly(conv(a, o.a));
    }

    // ---------- basic utilities ----------
    int deg() const { return (int)a.size() - 1; }
    void mod_xk(int k) { if ((int)a.size() > k) a.resize(k); }

    // ---------- calculus ----------
    Poly deri() const {
        if (a.size() <= 1) return Poly();
        vector<ll> r(a.size()-1);
        for (size_t i = 1; i < a.size(); ++i) r[i-1] = a[i] * (ll)i % MOD;
        return Poly(r);
    }
    Poly inte() const {
        vector<ll> r(a.size()+1);
        r[0] = 0;
        for (size_t i = 0; i < a.size(); ++i) r[i+1] = a[i] * invmod(i+1) % MOD;
        return Poly(r);
    }

    // ---------- inverse, log, exp ----------
    // inverse assumes a[0] != 0
    Poly inv() const {
        assert(!a.empty() && a[0] != 0);
        Poly R(vector<ll>{invmod(a[0])});

        int n = (int)a.size();
        int d = 1;
        while (d < n) {
            d <<= 1;
            vector<ll> f(d);
            for (int i = 0; i < (int)min(f.size(), a.size()); ++i) f[i] = a[i];
            Poly F(f);

            Poly FR = F * R;
            FR.mod_xk(d);
            for (auto &x : FR.a)
                x = (MOD - x) % MOD;
            FR.a[0] = (FR.a[0] + 2) % MOD;
            R = R * FR;
            R.mod_xk(d);
        }
        R.mod_xk(n);
        return R;
    }

    // log assumes a[0] == 1
    Poly log(int k = -1) const {
        int need = (k == -1 ? (int)a.size() : k);
        assert(!a.empty() && a[0] == 1);
        Poly res = (deri() * inv()).mod_xk_here(need).inte();
        res.mod_xk(need);
        return res;
    }

    // helper for chaining mod_xk without mutating original
    Poly mod_xk_here(int k) const { Poly r = *this; r.mod_xk(k); return r; }

    Poly exp() const {
        assert(!a.empty() && a[0] == 0);
        Poly R({1});
        int n = a.size();
        for (int len = 2; ; len <<= 1) {
            R.a.resize(len, 0);
            Poly Ln = R.log(len);
            Ln.a[0] = 1;
            for (int i = 1; i < len; ++i) {
                ll val = (i < n ? a[i] : 0);
                Ln.a[i] = val - Ln.a[i];
                if (Ln.a[i] < 0) Ln.a[i] += MOD;
            }
            R = R * Ln;
            R.mod_xk(len);

            if (len >= n) break;
        }

        R.mod_xk(n);
        return R;
    }
};
