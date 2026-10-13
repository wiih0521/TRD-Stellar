// Distance from p to segment [s,e]. Intended for Point<double>.
double segDist(Point<double> s, Point<double> e, Point<double> p) {
    if (s == e) return (p - s).dist();
    double d = (e - s).dist2();
    double t = min(d, max(0.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}
