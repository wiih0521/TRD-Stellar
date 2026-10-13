// matrix[i][j] = INF when there is no edge. O(n^3).
// Output -INF means that arbitrarily small walks exist.
void floydWarshall(vector<vector<ll>>& matrix) {
    const ll INF = (1LL << 62);
    int n = (int)matrix.size();
    for (int i = 0; i < n; ++i) matrix[i][i] = min(matrix[i][i], 0LL);
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (matrix[i][k] != INF && matrix[k][j] != INF)
                    matrix[i][j] = min(matrix[i][j],
                        max(-INF, matrix[i][k] + matrix[k][j]));
    for (int k = 0; k < n; ++k) if (matrix[k][k] < 0)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (matrix[i][k] != INF && matrix[k][j] != INF)
                    matrix[i][j] = -INF;
}
