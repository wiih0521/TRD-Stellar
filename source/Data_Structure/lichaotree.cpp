const ll INF = 1e18;

struct LichaoTree {
    using Node = pair<ll, ll>; // y = first * x + second

    long n;
    bool isMin;
    vector<Node> a;
    vector<char> has;

    LichaoTree(long _n, bool flag = true) : n(_n), isMin(flag) {
        assert(n > 0);
        a.assign(n * 4 + 4, {0, isMin ? INF : -INF});
        has.assign(n * 4 + 4, false);
    }

    ll f(Node line, ll x) const {
        return line.first * x + line.second;
    }

    bool better(Node lhs, Node rhs, ll x) const {
        return isMin ? f(lhs, x) < f(rhs, x) : f(lhs, x) > f(rhs, x);
    }

    void addLine(Node line, long l, long r, long id) {
        if (!has[id]) {
            a[id] = line;
            has[id] = true;
            return;
        }

        long mid = (l + r) >> 1;
        bool left = better(line, a[id], l);
        bool middle = better(line, a[id], mid);
        if (middle) swap(line, a[id]);
        if (l == r) return;

        if (left != middle) addLine(line, l, mid, id * 2);
        else addLine(line, mid + 1, r, id * 2 + 1);
    }

    void update(Node line) {
        addLine(line, 1, n, 1);
    }

    void update(Node line, long ql, long qr, long l, long r, long id) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            addLine(line, l, r, id);
            return;
        }

        long mid = (l + r) >> 1;
        update(line, ql, qr, l, mid, id * 2);
        update(line, ql, qr, mid + 1, r, id * 2 + 1);
    }

    // Adds line only for integer x in the closed interval [l, r].
    void update(Node line, long l, long r) {
        assert(1 <= l && l <= r && r <= n);
        update(line, l, r, 1, n, 1);
    }

    ll get(long x, long l, long r, long id) const {
        ll ans1 = f(a[id], x);
        if (l == r) return ans1;
        long mid = (l + r) >> 1;

        ll ans2;
        if (x <= mid) ans2 = get(x, l, mid, id * 2);
        else ans2 = get(x, mid + 1, r, id * 2 + 1);

        return isMin ? min(ans1, ans2) : max(ans1, ans2);
    }

    ll get(long x) const {
        assert(1 <= x && x <= n);
        return get(x, 1, n, 1);
    }
};
