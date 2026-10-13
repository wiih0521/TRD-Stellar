// Solves A*x=b over reals. Returns rank, or -1 if inconsistent.
// If rank < number of variables, one solution is returned (free variables = 0).
int solveLinear(vector<vector<double>>& A, vector<double>& b, vector<double>& x) {
    const double EPS = 1e-12;
    int n = (int)A.size(), m = n ? (int)A[0].size() : (int)x.size(), rank = 0;
    vector<int> where(m, -1);
    for (int col = 0; col < m && rank < n; ++col) {
        int pivot = rank;
        for (int r = rank + 1; r < n; ++r)
            if (abs(A[r][col]) > abs(A[pivot][col])) pivot = r;
        if (abs(A[pivot][col]) <= EPS) continue;
        swap(A[pivot], A[rank]); swap(b[pivot], b[rank]);
        where[col] = rank;
        for (int r = 0; r < n; ++r) if (r != rank) {
            double factor = A[r][col] / A[rank][col];
            b[r] -= factor * b[rank];
            for (int c = col; c < m; ++c) A[r][c] -= factor * A[rank][c];
        }
        ++rank;
    }
    for (int r = rank; r < n; ++r) if (abs(b[r]) > EPS) return -1;
    x.assign(m, 0);
    for (int col = 0; col < m; ++col)
        if (where[col] != -1) x[col] = b[where[col]] / A[where[col]][col];
    return rank;
}
