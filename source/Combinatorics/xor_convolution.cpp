// AND / OR / XOR subset convolution. Size must be a power of two.
enum class SubsetOp { AND, OR, XOR };
const long long SUBSET_MOD = 998244353;

long long subsetPower(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % SUBSET_MOD;
        a = a * a % SUBSET_MOD; e >>= 1;
    }
    return r;
}
void subsetTransform(vector<long long>& a, SubsetOp op, bool inverse) {
    int n = (int)a.size(); assert(n && !(n & (n - 1)));
    for (int step = 1; step < n; step <<= 1)
        for (int i = 0; i < n; i += 2 * step)
            for (int j = 0; j < step; ++j) {
                long long& x = a[i + j], &y = a[i + j + step];
                if (op == SubsetOp::XOR) {
                    long long u = x, v = y;
                    x = (u + v) % SUBSET_MOD;
                    y = (u - v + SUBSET_MOD) % SUBSET_MOD;
                } else if (op == SubsetOp::OR) {
                    y = (y + (inverse ? -x : x) + SUBSET_MOD) % SUBSET_MOD;
                } else {
                    x = (x + (inverse ? -y : y) + SUBSET_MOD) % SUBSET_MOD;
                }
            }
    if (inverse && op == SubsetOp::XOR) {
        long long inv = subsetPower(n, SUBSET_MOD - 2);
        for (long long& x : a) x = x * inv % SUBSET_MOD;
    }
}
vector<long long> subsetConvolution(vector<long long> a, vector<long long> b,
                                    SubsetOp op) {
    assert(a.size() == b.size());
    subsetTransform(a, op, false); subsetTransform(b, op, false);
    for (int i = 0; i < (int)a.size(); ++i) a[i] = a[i] * b[i] % SUBSET_MOD;
    subsetTransform(a, op, true);
    return a;
}
