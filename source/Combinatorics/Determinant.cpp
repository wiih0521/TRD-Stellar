double determinant(vector<vector<double>> a) {
    int n = (int)a.size(); double ans = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int r = i + 1; r < n; ++r)
            if (abs(a[r][i]) > abs(a[pivot][i])) pivot = r;
        if (abs(a[pivot][i]) < 1e-12) return 0;
        if (pivot != i) swap(a[pivot], a[i]), ans = -ans;
        ans *= a[i][i];
        for (int r = i + 1; r < n; ++r) {
            double factor = a[r][i] / a[i][i];
            for (int c = i + 1; c < n; ++c) a[r][c] -= factor * a[i][c];
        }
    }
    return ans;
}

// Works for composite moduli too. Inputs and mod must fit signed 64-bit.
long long determinantModulo(vector<vector<long long>> a, long long mod) {
    assert(mod > 0);
    int n = (int)a.size(); long long ans = 1 % mod;
    auto norm = [&](long long x) { x %= mod; return x < 0 ? x + mod : x; };
    auto mul = [&](long long x, long long y) {
        return (long long)((__int128)norm(x) * norm(y) % mod);
    };
    for (auto& row : a) for (long long& x : row) x = norm(x);
    for (int i = 0; i < n; ++i) {
        for (int r = i + 1; r < n; ++r) {
            while (a[r][i] != 0) {
                long long q = a[i][i] / a[r][i];
                for (int c = i; c < n; ++c)
                    a[i][c] = norm(a[i][c] - mul(q, a[r][c]));
                swap(a[i], a[r]);
                ans = norm(-ans);
            }
        }
        ans = mul(ans, a[i][i]);
        if (ans == 0) return 0;
    }
    return ans;
}
