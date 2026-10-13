// Solves A*x=b and marks every non-uniquely-determined x[i] as NaN.
// Returns rank, or -1 if inconsistent. A and b are destroyed. O(n*m*min(n,m)).
int solveLinearDetermined(vector<vector<double>>& A, vector<double>& b,
                          vector<double>& x) {
    const double EPS = 1e-12;
    int n = (int)A.size(), m = n ? (int)A[0].size() : (int)x.size(), rank = 0;
    vector<int> col(m); iota(col.begin(), col.end(), 0);
    while (rank < n && rank < m) {
        int pr = rank, pc = rank;
        for (int r = rank; r < n; ++r)
            for (int c = rank; c < m; ++c)
                if (abs(A[r][c]) > abs(A[pr][pc])) pr = r, pc = c;
        if (abs(A[pr][pc]) <= EPS) break;
        swap(A[rank], A[pr]); swap(b[rank], b[pr]);
        swap(col[rank], col[pc]);
        for (int r = 0; r < n; ++r) swap(A[r][rank], A[r][pc]);
        for (int r = 0; r < n; ++r) if (r != rank) {
            double factor = A[r][rank] / A[rank][rank];
            b[r] -= factor * b[rank];
            for (int c = rank; c < m; ++c) A[r][c] -= factor * A[rank][c];
        }
        ++rank;
    }
    for (int r = rank; r < n; ++r) if (abs(b[r]) > EPS) return -1;
    x.assign(m, numeric_limits<double>::quiet_NaN());
    for (int i = 0; i < rank; ++i) {
        bool fixed = true;
        for (int c = rank; c < m; ++c) fixed &= abs(A[i][c]) <= EPS;
        if (fixed) x[col[i]] = b[i] / A[i][i];
    }
    return rank;
}
