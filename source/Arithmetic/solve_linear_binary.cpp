// Solves A * x = b over F_2. Returns the rank, or -1 if no
// solution exists. A and b are destroyed; one solution is stored in x.
// Multiple solutions exist iff rank < m. Complexity: O(n^2 * m / word_size).

const int MAX_VARS = 1000;
using BS = bitset<MAX_VARS>;

int solveLinearBinary(vector<BS>& A, vector<int>& b, BS& x, int m) {
    int n = (int)A.size(), rank = 0;
    assert((int)b.size() == n && m <= MAX_VARS);

    vector<int> col(m);
    iota(col.begin(), col.end(), 0);

    for (int i = 0; i < n && i < m; ++i) {
        int br = -1, bc = -1;
        for (int r = i; r < n && br == -1; ++r) {
            for (int c = i; c < m; ++c) {
                if (A[r][c]) {
                    br = r;
                    bc = c;
                    break;
                }
            }
        }
        if (br == -1) {
            for (int j = i; j < n; ++j)
                if (b[j]) return -1;
            break;
        }

        swap(A[i], A[br]);
        swap(b[i], b[br]);
        swap(col[i], col[bc]);
        for (int j = 0; j < n; ++j) {
            if (A[j][i] != A[j][bc]) {
                A[j].flip(i);
                A[j].flip(bc);
            }
        }

        for (int j = i + 1; j < n; ++j) {
            if (A[j][i]) {
                A[j] ^= A[i];
                b[j] ^= b[i];
            }
        }
        ++rank;
    }

    for (int i = rank; i < n; ++i)
        if (b[i]) return -1;

    x.reset();
    for (int i = rank - 1; i >= 0; --i) {
        if (!b[i]) continue;
        x[col[i]] = 1;
        for (int j = 0; j < i; ++j) b[j] ^= A[j][i];
    }
    return rank;
}
