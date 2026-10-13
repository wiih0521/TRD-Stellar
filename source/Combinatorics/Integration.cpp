// Composite and adaptive Simpson integration.
template<class F>
double simpson(double a, double b, F f, int panels = 1000) {
    double h = (b - a) / (2 * panels), sum = f(a) + f(b);
    for (int i = 1; i < 2 * panels; ++i) sum += f(a + i * h) * (i & 1 ? 4 : 2);
    return sum * h / 3;
}

template<class F>
double adaptiveSimpsonRec(F& f, double a, double b, double eps,
                          double whole, int depth) {
    double c = (a + b) / 2;
    auto area = [&](double l, double r) {
        return (f(l) + 4 * f((l + r) / 2) + f(r)) * (r - l) / 6;
    };
    double left = area(a, c), right = area(c, b), sum = left + right;
    if (depth == 0 || abs(sum - whole) <= 15 * eps)
        return sum + (sum - whole) / 15;
    return adaptiveSimpsonRec(f, a, c, eps / 2, left, depth - 1) +
           adaptiveSimpsonRec(f, c, b, eps / 2, right, depth - 1);
}

template<class F>
double adaptiveSimpson(double a, double b, F f, double eps = 1e-9) {
    double whole = (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6;
    return adaptiveSimpsonRec(f, a, b, eps, whole, 30);
}
