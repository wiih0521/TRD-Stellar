// sa includes empty suffix n at sa[0]. lcp[i] = LCP(sa[i-1], sa[i]).
struct SuffixArray {
    vector<int> sa, lcp;
    explicit SuffixArray(string s, int lim = 256) {
        s.push_back('\0');
        int n = (int)s.size(), k = 0;
        vector<int> x(s.begin(), s.end()), y(n), ws(max(n, lim));
        sa.resize(n); lcp.assign(n, 0);
        iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1, 2 * j), lim = p) {
            p = j;
            iota(y.begin(), y.begin() + p, n - j);
            for (int i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; ++i) ++ws[x[i]];
            for (int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
            for (int i = n - 1; i >= 0; --i) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y); p = 1; x[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                int a = sa[i - 1], b = sa[i];
                x[b] = y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++;
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            int rank = x[i];
            if (rank == 0) { k = 0; continue; }
            if (k) --k;
            int j = sa[rank - 1];
            while (s[i + k] == s[j + k]) ++k;
            lcp[rank] = k;
        }
    }
};
