// Requires MillerRabin above.
namespace PollardRho {
using u64 = uint64_t;

u64 findFactor(u64 n) {
    if (!(n & 1)) return 2;
    if (n % 3 == 0) return 3;
    u64 x = 0, y = 0, iteration = 30, product = 2, constant = 1;
    auto advance = [&](u64 value) {
        return (u64)(((__uint128_t)MillerRabin::multiply(value, value, n)
                    + constant) % n);
    };
    while (iteration++ % 40 || gcd(product, n) == 1) {
        if (x == y) x = ++constant, y = advance(x);
        u64 difference = x > y ? x - y : y - x;
        u64 candidate = MillerRabin::multiply(product, difference, n);
        if (candidate) product = candidate;
        x = advance(x);
        y = advance(advance(y));
    }
    return gcd(product, n);
}

void factorRec(u64 n, map<u64, int>& factors) {
    if (n == 1) return;
    if (MillerRabin::isPrime64(n)) {
        ++factors[n];
        return;
    }
    u64 divisor = findFactor(n);
    factorRec(divisor, factors);
    factorRec(n / divisor, factors);
}

map<u64, int> factor(u64 n) {
    map<u64, int> result;
    factorRec(n, result);
    return result;
}
}
