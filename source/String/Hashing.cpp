// Arithmetic modulo 2^64-1; robust against structured anti-hash strings.
using ull = uint64_t;
struct Hash64 {
    ull x;
    Hash64(ull x = 0) : x(x) {}
    Hash64 operator+(Hash64 o) const { ull y = x + o.x; return y + (y < x); }
    Hash64 operator-(Hash64 o) const { return *this + Hash64(~o.x); }
    Hash64 operator*(Hash64 o) const {
        __uint128_t m = (__uint128_t)x * o.x;
        return Hash64((ull)m) + Hash64((ull)(m >> 64));
    }
    ull get() const { return x + (x == ULLONG_MAX); }
    bool operator==(Hash64 o) const { return get() == o.get(); }
    bool operator<(Hash64 o) const { return get() < o.get(); }
};
const Hash64 HASH_BASE = 100000000003ULL;

struct StringHash {
    vector<Hash64> pref, power;
    explicit StringHash(const string& s) : pref(s.size() + 1), power(s.size() + 1) {
        power[0] = 1;
        for (int i = 0; i < (int)s.size(); ++i) {
            pref[i + 1] = pref[i] * HASH_BASE + (unsigned char)s[i] + 1;
            power[i + 1] = power[i] * HASH_BASE;
        }
    }
    Hash64 get(int l, int r) const {
        assert(0 <= l && l <= r && r < (int)pref.size());
        return pref[r] - pref[l] * power[r - l];
    }
};
