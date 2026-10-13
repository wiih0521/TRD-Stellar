// Gaussian elimination modulo prime MOD_GAUSS. Returns rank or -1 if inconsistent.
const long long MOD_GAUSS = 1000000009;
long long gaussPower(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD_GAUSS;
        a = a * a % MOD_GAUSS; e >>= 1;
    }
    return r;
}
int solveLinearMod(vector<vector<long long>>& A, vector<long long>& b,
                   vector<long long>& x) {
    int n = (int)A.size(), m = n ? (int)A[0].size() : (int)x.size(), rank = 0;
    auto norm = [](long long v) { v %= MOD_GAUSS; return v < 0 ? v + MOD_GAUSS : v; };
    vector<int> where(m, -1);
    for (auto& row : A) for (long long& v : row) v = norm(v);
    for (long long& v : b) v = norm(v);
    for (int col = 0; col < m && rank < n; ++col) {
        int pivot = rank;
        while (pivot < n && A[pivot][col] == 0) ++pivot;
        if (pivot == n) continue;
        swap(A[pivot], A[rank]); swap(b[pivot], b[rank]);
        where[col] = rank;
        long long inv = gaussPower(A[rank][col], MOD_GAUSS - 2);
        for (int c = col; c < m; ++c) A[rank][c] = A[rank][c] * inv % MOD_GAUSS;
        b[rank] = b[rank] * inv % MOD_GAUSS;
        for (int r = 0; r < n; ++r) if (r != rank && A[r][col]) {
            long long factor = A[r][col];
            for (int c = col; c < m; ++c)
                A[r][c] = norm(A[r][c] - factor * A[rank][c] % MOD_GAUSS);
            b[r] = norm(b[r] - factor * b[rank] % MOD_GAUSS);
        }
        ++rank;
    }
    for (int r = rank; r < n; ++r) if (b[r]) return -1;
    x.assign(m, 0);
    for (int col = 0; col < m; ++col) if (where[col] != -1) x[col] = b[where[col]];
    return rank;
}
