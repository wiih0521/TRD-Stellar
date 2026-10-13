template<class T>
struct Matrix {
    int rows, cols;
    vector<vector<T>> a;
    Matrix(int rows = 0, int cols = 0, T value = T())
        : rows(rows), cols(cols), a(rows, vector<T>(cols, value)) {}
    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }

    static Matrix identity(int n) {
        Matrix result(n, n);
        for (int i = 0; i < n; ++i) result[i][i] = T(1);
        return result;
    }
    Matrix operator*(const Matrix& other) const {
        assert(cols == other.rows);
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int k = 0; k < cols; ++k)
                for (int j = 0; j < other.cols; ++j)
                    result[i][j] = result[i][j] + a[i][k] * other[k][j];
        return result;
    }
    Matrix power(long long exponent) const {
        assert(rows == cols && exponent >= 0);
        Matrix base = *this, result = identity(rows);
        while (exponent) {
            if (exponent & 1) result = result * base;
            base = base * base;
            exponent >>= 1;
        }
        return result;
    }
};
