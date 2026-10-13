// Closest pair of integer points in O(n log n). Requires at least 2 points.
using P = Point<ll>;
pair<P, P> closestPair(vector<P> points) {
    assert(points.size() > 1);
    set<P> active;
    sort(points.begin(), points.end(), [](P a, P b) {
        return tie(a.y, a.x) < tie(b.y, b.x);
    });
    pair<ll, pair<P, P>> best{LLONG_MAX, {P(), P()}};
    int left = 0;
    for (P point : points) {
        ll width = 1 + (ll)sqrt((long double)best.first);
        P delta(width, 0);
        while (left < (int)points.size() &&
               points[left].y <= point.y - width)
            active.erase(points[left++]);
        auto low = active.lower_bound(point - delta);
        auto high = active.upper_bound(point + delta);
        for (; low != high; ++low)
            best = min(best, {(*low - point).dist2(), {*low, point}});
        active.insert(point);
    }
    return best.second;
}
