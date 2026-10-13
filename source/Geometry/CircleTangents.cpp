// External tangents of two circles; negate r2 for internal tangents.
// Returns 0, 1, or 2 pairs of tangency points.
template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
    P d = c2 - c1;
    double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) return {};
    vector<pair<P, P>> out;
    for (double sign : {-1.0, 1.0}) {
        P v = (d * dr + d.perp() * sqrt(max(0.0, h2)) * sign) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    if (h2 == 0) out.pop_back();
    return out;
}
