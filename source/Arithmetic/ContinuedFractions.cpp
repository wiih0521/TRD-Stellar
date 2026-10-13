// Closest p/q to x with 0 <= p,q <= limit. O(log limit).
pair<ll, ll> rationalApprox(long double x, ll limit) {
    ll lp = 0, lq = 1, p = 1, q = 0;
    long double y = x;
    while (true) {
        ll inf = LLONG_MAX;
        ll boundP = p ? (limit - lp) / p : inf;
        ll boundQ = q ? (limit - lq) / q : inf;
        ll a = (ll)floor(y), b = min(a, min(boundP, boundQ));
        ll np = b * p + lp, nq = b * q + lq;
        if (a > b) {
            long double first = nq ? fabsl(x - (long double)np / nq) : 1e100L;
            long double second = q ? fabsl(x - (long double)p / q) : 1e100L;
            return first < second ? make_pair(np, nq) : make_pair(p, q);
        }
        long double rem = y - a;
        if (fabsl(rem) < 1e-30L) return {np, nq};
        y = 1 / rem;
        if (fabsl(y) > 3 * (long double)limit) return {np, nq};
        lp = p; p = np;
        lq = q; q = nq;
    }
}
