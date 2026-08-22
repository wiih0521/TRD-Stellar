
/* GAUSS ELIMINATION YAHOOO! */

void gauss(vector<vector<double>>& a, vector<double>& b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[j][i]) {
                double ratio = a[j][i] / a[i][i];
                for (int k = i; k < n; ++k) a[j][k] -= ratio * a[i][k];
                b[j] -= ratio * b[i];
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) b[i] -= a[i][j] * b[j];
        b[i] /= a[i][i];
    }
}