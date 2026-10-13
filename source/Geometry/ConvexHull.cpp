// Strict convex hull in CCW order; removes collinear points on edges.
// O(n log n). Duplicate input points are allowed.
using P = Point<ll>;
vector<P> convexHull(vector<P> points) {
    if (points.size() <= 1) return points;
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    if (points.size() <= 1) return points;

    vector<P> hull(points.size() + 1);
    int start = 0, top = 0;
    for (int pass = 0; pass < 2; ++pass) {
        for (P p : points) {
            while (top >= start + 2 &&
                   hull[top - 2].cross(hull[top - 1], p) <= 0)
                --top;
            hull[top++] = p;
        }
        start = --top;
        reverse(points.begin(), points.end());
    }
    hull.resize(top);
    return hull;
}
