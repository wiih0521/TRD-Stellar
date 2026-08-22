struct Matrix {
    int n, m;
    vector<vector<Modular>> a;

    Matrix(int n, int m) : n(n), m(m), a(n, vector<Modular>(m)) {}

    vector<Modular>& operator[] (int i) { return a[i]; }
    const vector<Modular>& operator[] (int i) const { return a[i]; }

    void read() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
    }

    void print() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " \n"[j + 1 == m];
            }
        }
    }

    static Matrix eye(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    Matrix operator *(const Matrix& b) {
        assert(m == b.n);
        Matrix res(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < b.m; k++) {
                for (int j = 0; j < m; j++) {
                    res[i][k] += a[i][j] * b[j][k];
                }
            }
        }
        return res;
    }

    Matrix pow(long long k) const {
        assert(n == m);
        Matrix res = eye(n);
        Matrix base = *this;
        while (k > 0) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }

    Modular det() const {
        assert(n == m);
        Matrix tmp = *this;
        Modular ans = 1;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                while (tmp[j][i].x != 0) {
                    ll t = tmp[i][i].x / tmp[j][i].x;

                    if (t != 0) {
                        Modular factor(t);
                        for (int k = i; k < n; k++) {
                            tmp[i][k] -= tmp[j][k] * factor;
                        }
                    }

                    swap(tmp[i], tmp[j]);
                    ans *= Modular(-1);
                }
            }

            ans *= tmp[i][i];
            if (ans.x == 0) return 0;
        }
        return ans;
    }
};
