// Golden-section search: argument minimizing a unimodal f on [lo, hi].
template<class F>
double goldenSearch(double lo, double hi, F f, double eps = 1e-9) {
    const double ratio = (sqrt(5.0) - 1) / 2;
    double x1 = hi - ratio * (hi - lo), x2 = lo + ratio * (hi - lo);
    double f1 = f(x1), f2 = f(x2);
    while (hi - lo > eps) {
        if (f1 < f2) {
            hi = x2; x2 = x1; f2 = f1;
            x1 = hi - ratio * (hi - lo); f1 = f(x1);
        } else {
            lo = x1; x1 = x2; f1 = f2;
            x2 = lo + ratio * (hi - lo); f2 = f(x2);
        }
    }
    return (lo + hi) / 2;
}

using Point2 = array<double, 2>;
template<class F>
pair<double, Point2> hillClimb(Point2 start, F f, double step = 1e9) {
    pair<double, Point2> best = {f(start), start};
    for (; step > 1e-12; step /= 2) {
        for (int repeat = 0; repeat < 60; ++repeat)
            for (int dx = -1; dx <= 1; ++dx)
                for (int dy = -1; dy <= 1; ++dy) {
                    Point2 p = {best.second[0] + dx * step, best.second[1] + dy * step};
                    best = min(best, make_pair(f(p), p));
                }
    }
    return best;
}
