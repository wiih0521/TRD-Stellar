/*
Xor convolution:
- Usage: xormul(a, b, &c);
*/


const int mod = 998244353;

int inverse(int x, int mod) {
    return x == 1 ? 1 : mod - mod / x * inverse(mod % x, mod) % mod;
}

void xormul(vector<int> a, vector<int> b, vector<int> &c) {
    int m = (int) a.size();
    c.resize(m);
    for (int n = m / 2; n > 0; n /= 2)
        for (int i = 0; i < m; i += 2 * n)
            for (int j = 0; j < n; j++) {
                int x = a[i + j], y = a[i + j + n];
                a[i + j] = (x + y) % mod;
                a[i + j + n] = (x - y + mod) % mod;
            }
    for (int n = m / 2; n > 0; n /= 2)
        for (int i = 0; i < m; i += 2 * n)
            for (int j = 0; j < n; j++) {
                int x = b[i + j], y = b[i + j + n];
                b[i + j] = (x + y) % mod;
                b[i + j + n] = (x - y + mod) % mod;
            }
    for (int i = 0; i < m; i++)
        c[i] = a[i] * b[i] % mod;
    for (int n = 1; n < m; n *= 2)
        for (int i = 0; i < m; i += 2 * n)
            for (int j = 0; j < n; j++) {
                int x = c[i + j], y = c[i + j + n];
                c[i + j] = (x + y) % mod;
                c[i + j + n] = (x - y + mod) % mod;
            }
    int mrev = inverse(m, mod);
    for (int i = 0; i < m; i++)
        c[i] = c[i] * mrev % mod;
}