// Recovers prefix sum of f from prefix sums of g and f*g modulo a prime.
struct DirichletSummatory {
    using Function = ll(*)(ll);
    ll limit = 0, inverse = 0, mod;
    Function prefixF, prefixG, prefixConvolution;
    unordered_map<ll, ll> memo;

    DirichletSummatory(Function prefixF, Function prefixG,
            Function prefixConvolution, ll mod)
        : mod(mod), prefixF(prefixF), prefixG(prefixG),
          prefixConvolution(prefixConvolution) {}

    ll power(ll base, ll exponent) const {
        ll result = 1;
        while (exponent) {
            if (exponent & 1) result = (__int128)result * base % mod;
            base = (__int128)base * base % mod;
            exponent >>= 1;
        }
        return result;
    }

    ll calculate(ll x) {
        if (x <= limit) return (prefixF(x) % mod + mod) % mod;
        auto found = memo.find(x);
        if (found != memo.end()) return found->second;
        ll subtracted = 0;
        for (ll left = 2, right; left <= x; left = right + 1) {
            right = x / (x / left);
            ll sumG = (prefixG(right) - prefixG(left - 1)) % mod;
            if (sumG < 0) sumG += mod;
            subtracted = (subtracted
                + (__int128)sumG * calculate(x / left)) % mod;
        }
        ll answer = (prefixConvolution(x) - subtracted) % mod;
        if (answer < 0) answer += mod;
        return memo[x] = (__int128)answer * inverse % mod;
    }

    // prefixF(x) must be directly available for x <= directLimit.
    ll solve(ll n, ll directLimit) {
        limit = directLimit;
        memo.clear();
        ll first = (prefixG(1) % mod + mod) % mod;
        assert(first != 0);
        inverse = power(first, mod - 2);
        return calculate(n);
    }
};
