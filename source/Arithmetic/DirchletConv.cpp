struct Dirchlet
{
    typedef ll(*func) (ll);
    ll n, lim, inv;
    func p_f, p_g, p_fg;
    unordered_map<ll, ll> mem;
    Dirchlet() {}
    Dirchlet(func x, func y, func z) : p_f(x), p_g(y), p_fg(z) {}
    ll calc(ll x)
    {
        if (x <= lim) return p_f(x);
        auto d = mem.find(x);
        if (d != mem.end()) return d->second;
        ll ans = 0;
        for (ll i = 2, la; i <= x; i = la + 1)
        {
            la = x / (x / i);
            ans = ans + (p_g(la) - p_g(i - 1) + MOD) * calc(x / i) % MOD;
            if (ans >= MOD) ans -= MOD;
        }
        ans %= MOD;
        ans = p_fg(x) - ans;
        if (ans < 0) ans += MOD;
        ans = 1ll * ans * inv % MOD;
        return mem[x] = ans;
    }
    ll solve(ll n_, ll lim_)
    {
        n = n_, lim = lim_;
        inv = bin_pow(p_g(1), MOD - 2);
        return calc(n);
    }
};