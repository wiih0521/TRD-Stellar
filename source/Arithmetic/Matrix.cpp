// need Modular arithmetic structure to run
// ex: matrix a(n, n), a.det(); a.pow(k);

struct matrix {
    int n, m;
    vector<vector<Modular>> a;

    matrix(int n, int m) : n(n), m(m), a(n, vector<Modular>(m)) {}

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

    static matrix eye(int n) {
        matrix res(n, n);
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }

    matrix operator *(const matrix& b) {
        assert(m == b.n);
        matrix res(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < b.m; k++) {
                for (int j = 0; j < m; j++) {
                    res[i][k] += a[i][j] * b[j][k];
                }
            }
        }
        return res;
    }

    matrix pow(long long k) const {
        assert(n == m);
        matrix res = eye(n);
        matrix base = *this;
        while (k > 0) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }

    Modular det() const {
        assert(n == m);
        matrix tmp = *this;
        Modular res = 1;

        for (int i = 0; i < n; i++) {
            int pivot = i;
            while (pivot < n && tmp[pivot][i].x == 0) pivot++;

            if (pivot == n) return 0;

            if (pivot != i) {
                swap(tmp.a[i], tmp.a[pivot]);
                res = res * Modular(-1);
            }

            res *= tmp[i][i];
            Modular inv = inverse(tmp[i][i]);

            for (int j = i; j < n; j++) {
                tmp[i][j] *= inv;
            }

            for (int j = 0; j < n; j++) {
                if (j != i && tmp[j][i].x != 0) {
                    Modular factor = tmp[j][i];
                    for (int k = i; k < n; k++) {
                        tmp[j][k] -= factor * tmp[i][k];
                    }
                }
            }
        }
        return res;
    }
};
