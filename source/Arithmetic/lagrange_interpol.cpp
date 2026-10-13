// Coefficients of the unique degree < n polynomial through (x[i],y[i]).
// mod must be prime and x values must be distinct modulo mod. O(n^3).
vector<ll> lagrangePolynomial(
        const vector<ll>& x, const vector<ll>& y, ll mod) {
    int n = (int)x.size();
    assert((int)y.size() == n);
    auto power = [&](ll base, ll exponent) {
        ll result = 1;
        while (exponent) {
            if (exponent & 1) result = (__int128)result * base % mod;
            base = (__int128)base * base % mod;
            exponent >>= 1;
        }
        return result;
    };
    vector<ll> answer(n);
    for (int chosen = 0; chosen < n; ++chosen) {
        vector<ll> basis(1, 1);
        ll denominator = 1;
        for (int other = 0; other < n; ++other) if (other != chosen) {
            vector<ll> next(basis.size() + 1);
            ll root = (x[other] % mod + mod) % mod;
            for (int degree = 0; degree < (int)basis.size(); ++degree) {
                next[degree + 1] =
                    (next[degree + 1] + basis[degree]) % mod;
                next[degree] =
                    (next[degree] - (__int128)root * basis[degree]) % mod;
                if (next[degree] < 0) next[degree] += mod;
            }
            basis.swap(next);
            ll difference = (x[chosen] - x[other]) % mod;
            if (difference < 0) difference += mod;
            denominator = (__int128)denominator * difference % mod;
        }
        assert(denominator != 0);
        ll scale = (__int128)((y[chosen] % mod + mod) % mod)
                 * power(denominator, mod - 2) % mod;
        for (int degree = 0; degree < n; ++degree)
            answer[degree] =
                (answer[degree] + (__int128)basis[degree] * scale) % mod;
    }
    return answer;
}
