/*
Usage:
- conv: multiply A and B modulo 998244353
*/



namespace PolyMul {

    using namespace std;
    using cd = complex<double>;
    const double PI = acos(-1);

    // Perform FFT or inverse FFT
    void fft(vector<cd>& a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; ++j) {
                    cd u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) for (cd& x : a) x /= n;
    }

    // Multiply two polynomials
    vector<double> multiply(const vector<double>& a, const vector<double>& b) {
        int n = 1;
        int total_size = a.size() + b.size() - 1;
        while (n < total_size) n <<= 1;  // Ensure n is a power of two

        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i) fa[i] *= fb[i];
        fft(fa, true);

        vector<double> result(total_size);
        for (int i = 0; i < total_size; ++i) result[i] = fa[i].real();
        return result;
    }
}