// sum_{i=0}^{to-1} floor((k*i+c)/m), for non-negative arguments.
using u64 = uint64_t;

u64 arithmeticSum(u64 n) {
    return n / 2 * ((n - 1) | 1); // avoids overflow in n*(n-1)/2
}

u64 divSum(u64 to, u64 c, u64 k, u64 m) {
    u64 result = k / m * arithmeticSum(to) + c / m * to;
    k %= m;
    c %= m;
    if (!k) return result;
    u64 rows = (to * k + c) / m;
    return result + (to - 1) * rows - divSum(rows, m - 1 - c, m, k);
}

// sum_{i=0}^{to-1} ((k*i+c) mod m). Result must fit in signed 64-bit.
ll modSum(u64 to, ll c, ll k, ll m) {
    c = (c % m + m) % m;
    k = (k % m + m) % m;
    return (ll)(to * c + k * arithmeticSum(to)
              - m * divSum(to, c, k, m));
}
