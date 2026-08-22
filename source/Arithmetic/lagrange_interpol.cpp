
typedef long long ll;

// Function to compute (base^exp) % mod
ll mod_exp(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Function to compute modular inverse using Fermat's Little Theorem
ll mod_inv(ll a, ll mod) {
    return mod_exp(a, mod - 2, mod);
}

// Function to add two polynomials
std::vector<ll> add_polynomials(const std::vector<ll>& a, const std::vector<ll>& b) {
    std::vector<ll> result(std::max(a.size(), b.size()));
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < a.size()) result[i] = (result[i] + a[i]) % MOD;
        if (i < b.size()) result[i] = (result[i] + b[i]) % MOD;
    }
    return result;
}

// Function to multiply a polynomial by a monomial (x - c)
std::vector<ll> multiply_polynomial(const std::vector<ll>& poly, ll c) {
    std::vector<ll> result(poly.size() + 1);
    for (size_t i = 0; i < poly.size(); ++i) {
        result[i + 1] = poly[i];
        result[i] = (result[i] - c * poly[i] % MOD + MOD) % MOD;
    }
    return result;
}

// Function to multiply a polynomial by a constant
std::vector<ll> multiply_by_constant(const std::vector<ll>& poly, ll constant) {
    std::vector<ll> result(poly.size());
    for (size_t i = 0; i < poly.size(); ++i) {
        result[i] = poly[i] * constant % MOD;
    }
    return result;
}

// Function for Lagrange interpolation to find the polynomial
std::vector<ll> lagrange_polynomial(const std::vector<ll>& x_vals, const std::vector<ll>& y_vals) {
    int n = x_vals.size();
    std::vector<ll> poly(n, 0);

    for (int i = 0; i < n; ++i) {
        ll denom = 1;
        std::vector<ll> term = {y_vals[i]};
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                denom = denom * (x_vals[i] - x_vals[j] + MOD) % MOD;
                term = multiply_polynomial(term, x_vals[j]);
            }
        }
        ll inv_denom = mod_inv(denom, MOD);
        term = multiply_by_constant(term, inv_denom);
        poly = add_polynomials(poly, term);
    }

    return poly;
}
