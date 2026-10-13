// Point in strict CCW convex hull without collinear vertices. O(log n).
using P = Point<ll>;
bool inHull(const vector<P>& hull, P point, bool strict = true) {
    int n = (int)hull.size(), a = 1, b = n - 1, boundary = !strict;
    if (n == 0) return false;
    if (n < 3) return boundary && onSegment(hull[0], hull.back(), point);
    if (sideOf(hull[0], hull[a], hull[b]) > 0) swap(a, b);
    if (sideOf(hull[0], hull[a], point) >= boundary ||
        sideOf(hull[0], hull[b], point) <= -boundary)
        return false;
    while (abs(a - b) > 1) {
        int middle = (a + b) / 2;
        if (sideOf(hull[0], hull[middle], point) > 0) b = middle;
        else a = middle;
    }
    return sgn(hull[a].cross(hull[b], point)) < boundary;
}
