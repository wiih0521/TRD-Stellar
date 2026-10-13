struct RealPolynomial {
    vector<double> a; // a[i] * x^i
    double operator()(double x) const {
        double value = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i) value = value * x + a[i];
        return value;
    }
    RealPolynomial derivative() const {
        if (a.size() <= 1) return {{0}};
        vector<double> d(a.size() - 1);
        for (int i = 1; i < (int)a.size(); ++i) d[i - 1] = i * a[i];
        return {d};
    }
    void divideByRoot(double root) { // assumes root is a root
        for (int i = (int)a.size() - 2; i >= 0; --i) a[i] += root * a[i + 1];
        a.erase(a.begin());
    }
};

vector<double> realRoots(RealPolynomial p, double lo, double hi) {
    while (p.a.size() > 1 && abs(p.a.back()) < 1e-14) p.a.pop_back();
    if (p.a.size() <= 1) return {};
    if (p.a.size() == 2) {
        double x = -p.a[0] / p.a[1];
        return lo - 1e-10 <= x && x <= hi + 1e-10 ? vector<double>{x} : vector<double>{};
    }
    vector<double> critical = realRoots(p.derivative(), lo, hi), cuts{lo};
    cuts.insert(cuts.end(), critical.begin(), critical.end());
    cuts.push_back(hi);
    vector<double> roots;
    if (abs(p(lo)) < 1e-8) roots.push_back(lo);
    if (abs(p(hi)) < 1e-8) roots.push_back(hi);
    for (double x : critical) if (abs(p(x)) < 1e-8) roots.push_back(x);
    for (int i = 0; i + 1 < (int)cuts.size(); ++i) {
        double l = cuts[i], r = cuts[i + 1], fl = p(l), fr = p(r);
        if ((fl < 0) == (fr < 0) || fl == 0 || fr == 0) continue;
        for (int it = 0; it < 80; ++it) {
            double m = (l + r) / 2, fm = p(m);
            if ((fl < 0) == (fm < 0)) l = m, fl = fm;
            else r = m;
        }
        roots.push_back((l + r) / 2);
    }
    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end(), [](double x, double y) {
        return abs(x - y) < 1e-7;
    }), roots.end());
    return roots;
}

// Coefficients of the degree < n polynomial through (x[i], y[i]). O(n^2).
vector<double> interpolatePolynomial(vector<double> x, vector<double> y) {
    int n = (int)x.size(); assert((int)y.size() == n);
    vector<double> result(n), basis(n); basis[0] = 1;
    for (int k = 0; k < n; ++k) {
        double denom = 1;
        for (int j = 0; j < k; ++j) denom *= x[k] - x[j];
        assert(abs(denom) > 1e-15);
        double coef = y[k];
        if (k > 0) {
            double known = 0;
            for (int i = n - 1; i >= 0; --i) known = known * x[k] + result[i];
            coef = y[k] - known;
        }
        coef /= denom;
        for (int i = 0; i < n; ++i) result[i] += coef * basis[i];
        if (k + 1 < n) {
            for (int i = k + 1; i >= 1; --i)
                basis[i] = basis[i - 1] - x[k] * basis[i];
            basis[0] *= -x[k];
        }
    }
    return result;
}
