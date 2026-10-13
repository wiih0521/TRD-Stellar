// Inverts A in place using full pivoting. Returns rank; rank < n means singular.
int matrixInverse(vector<vector<double>>& A) {
    const double EPS = 1e-12;
    int n = (int)A.size();
    vector<int> col(n); iota(col.begin(), col.end(), 0);
    vector<vector<double>> inv(n, vector<double>(n));
    for (int i = 0; i < n; ++i) inv[i][i] = 1;
    for (int i = 0; i < n; ++i) {
        int pr = i, pc = i;
        for (int r = i; r < n; ++r)
            for (int c = i; c < n; ++c)
                if (abs(A[r][c]) > abs(A[pr][pc])) pr = r, pc = c;
        if (abs(A[pr][pc]) < EPS) return i;
        swap(A[i], A[pr]); swap(inv[i], inv[pr]);
        for (int r = 0; r < n; ++r) swap(A[r][i], A[r][pc]);
        swap(col[i], col[pc]);
        double pivot = A[i][i];
        for (int c = 0; c < n; ++c) A[i][c] /= pivot, inv[i][c] /= pivot;
        for (int r = 0; r < n; ++r) if (r != i) {
            double factor = A[r][i];
            for (int c = 0; c < n; ++c) {
                A[r][c] -= factor * A[i][c];
                inv[r][c] -= factor * inv[i][c];
            }
        }
    }
    vector<vector<double>> answer(n, vector<double>(n));
    for (int i = 0; i < n; ++i) answer[col[i]] = inv[i];
    A = move(answer);
    return n;
}
