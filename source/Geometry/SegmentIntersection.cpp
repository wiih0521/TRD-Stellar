// Returns 0, 1, or 2 points. Two points describe the common segment.
// With integer points, a non-integral unique intersection is truncated.
template<class P>
vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b);
    auto oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> intersections;
    if (onSegment(c, d, a)) intersections.insert(a);
    if (onSegment(c, d, b)) intersections.insert(b);
    if (onSegment(a, b, c)) intersections.insert(c);
    if (onSegment(a, b, d)) intersections.insert(d);
    return {intersections.begin(), intersections.end()};
}
