// Barrett reduction for a fixed runtime modulus b. reduce(a) is in [0, 2b).
// Use reduce(a) % b only when a canonical remainder is required.
using ull = unsigned long long;
struct FastMod {
    ull b, m;
    explicit FastMod(ull mod) : b(mod), m(mod ? ULLONG_MAX / mod : 0) { assert(mod > 0); }
    ull reduce(ull a) const {
        return a - (ull)(((__uint128_t)m * a) >> 64) * b;
    }
};
