// 1 / 0 / -1 means left / on / right of directed line s->e.
template<class P>
int sideOf(P s, P e, P p) {
    return sgn(s.cross(e, p));
}

template<class P>
int sideOf(P s, P e, P p, double eps) {
    auto area = (e - s).cross(p - s);
    double tolerance = (e - s).dist() * eps;
    return (area > tolerance) - (area < -tolerance);
}
