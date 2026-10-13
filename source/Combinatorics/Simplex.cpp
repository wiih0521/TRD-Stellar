// Maximize c^T x subject to A*x <= b and x >= 0.
// Returns -INF if infeasible, +INF if unbounded; otherwise an optimum. O(nm*pivots).
struct LPSolver {
    using Vec = vector<double>;
    static double eps() { return 1e-9; }
    static double inf() { return numeric_limits<double>::infinity(); }
    int m, n;
    vector<int> nonbasic, basic;
    vector<Vec> tab;

    LPSolver(const vector<Vec>& A, const Vec& b, const Vec& c)
        : m((int)b.size()), n((int)c.size()), nonbasic(n + 1), basic(m),
          tab(m + 2, Vec(n + 2)) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) tab[i][j] = A[i][j];
        for (int i = 0; i < m; ++i) {
            basic[i] = n + i; tab[i][n] = -1; tab[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; ++j) nonbasic[j] = j, tab[m][j] = -c[j];
        nonbasic[n] = -1; tab[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        double inv = 1 / tab[r][s];
        for (int i = 0; i < m + 2; ++i) if (i != r)
            for (int j = 0; j < n + 2; ++j) if (j != s)
                tab[i][j] -= tab[r][j] * tab[i][s] * inv;
        for (int j = 0; j < n + 2; ++j) if (j != s) tab[r][j] *= inv;
        for (int i = 0; i < m + 2; ++i) if (i != r) tab[i][s] *= -inv;
        tab[r][s] = inv;
        swap(basic[r], nonbasic[s]);
    }

    bool simplex(int phase) {
        int objective = m + phase - 1;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; ++j) {
                if (nonbasic[j] == -phase) continue;
                if (s == -1 || make_pair(tab[objective][j], nonbasic[j]) <
                               make_pair(tab[objective][s], nonbasic[s])) s = j;
            }
            if (tab[objective][s] >= -eps()) return true;
            int r = -1;
            for (int i = 0; i < m; ++i) if (tab[i][s] > eps()) {
                pair<double, int> cur = {tab[i][n + 1] / tab[i][s], basic[i]};
                if (r == -1 || cur < make_pair(tab[r][n + 1] / tab[r][s], basic[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    double solve(Vec& x) {
        if (m == 0) {
            x.assign(n, 0);
            for (int j = 0; j < n; ++j) if (tab[m][j] < -eps()) return inf();
            return 0;
        }
        int r = min_element(tab.begin(), tab.begin() + m,
            [&](const Vec& a, const Vec& b) { return a[n + 1] < b[n + 1]; }) - tab.begin();
        if (tab[r][n + 1] < -eps()) {
            pivot(r, n);
            if (!simplex(2) || tab[m + 1][n + 1] < -eps()) return -inf();
            for (int i = 0; i < m; ++i) if (basic[i] == -1) {
                int s = 0;
                for (int j = 1; j <= n; ++j)
                    if (make_pair(tab[i][j], nonbasic[j]) < make_pair(tab[i][s], nonbasic[s])) s = j;
                pivot(i, s);
            }
        }
        if (!simplex(1)) return inf();
        x.assign(n, 0);
        for (int i = 0; i < m; ++i) if (basic[i] < n) x[basic[i]] = tab[i][n + 1];
        return tab[m][n + 1];
    }
};
