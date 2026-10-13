// Solves diag*x + super/sub diagonals = rhs. Stable for diagonally dominant matrices.
vector<double> solveTridiagonal(vector<double> diag, const vector<double>& super,
                                const vector<double>& sub, vector<double> rhs) {
    int n = (int)diag.size();
    assert((int)rhs.size() == n && (int)super.size() == max(0, n - 1) &&
           (int)sub.size() == max(0, n - 1));
    for (int i = 0; i + 1 < n; ++i) {
        assert(abs(diag[i]) > 1e-15);
        double factor = sub[i] / diag[i];
        diag[i + 1] -= factor * super[i];
        rhs[i + 1] -= factor * rhs[i];
    }
    vector<double> x(n);
    if (n == 0) return x;
    assert(abs(diag[n - 1]) > 1e-15);
    x[n - 1] = rhs[n - 1] / diag[n - 1];
    for (int i = n - 2; i >= 0; --i)
        x[i] = (rhs[i] - super[i] * x[i + 1]) / diag[i];
    return x;
}
