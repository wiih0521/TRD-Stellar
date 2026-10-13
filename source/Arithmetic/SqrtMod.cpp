// Tonelli-Shanks: one x with x^2 == a (mod odd prime p), or -1.
ll modSqrt(ll a, ll p) {
    auto power = [&](ll base, ll exponent) {
        ll result = 1;
        while (exponent) {
            if (exponent & 1) result = (__int128)result * base % p;
            base = (__int128)base * base % p;
            exponent >>= 1;
        }
        return result;
    };
    a = (a % p + p) % p;
    if (a == 0 || p == 2) return a;
    if (power(a, (p - 1) / 2) != 1) return -1;
    if (p % 4 == 3) return power(a, (p + 1) / 4);
    ll odd = p - 1;
    int exponent = 0;
    while (!(odd & 1)) odd >>= 1, ++exponent;
    ll nonSquare = 2;
    while (power(nonSquare, (p - 1) / 2) != p - 1) ++nonSquare;
    ll x = power(a, (odd + 1) / 2);
    ll value = power(a, odd);
    ll generator = power(nonSquare, odd);
    while (value != 1) {
        ll current = value;
        int index = 0;
        while (current != 1) {
            current = (__int128)current * current % p;
            ++index;
        }
        ll correction = power(generator, 1LL << (exponent - index - 1));
        x = (__int128)x * correction % p;
        generator = (__int128)correction * correction % p;
        value = (__int128)value * generator % p;
        exponent = index;
    }
    return x;
}
