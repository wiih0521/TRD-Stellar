
using P = Point<double>;

// Expected O(n). Empty input returns center (0,0), radius 0.
pair<P, double> minimumEnclosingCircle(vector<P> points) {
    if (points.empty()) return {P(0, 0), 0};
    shuffle(points.begin(), points.end(), rng);
    P center = points[0];
    double radius = 0, tolerance = 1 + 1e-8;
    for (int i = 0; i < (int)points.size(); ++i) {
        if ((center - points[i]).dist() <= radius * tolerance) continue;
        center = points[i];
        radius = 0;
        for (int j = 0; j < i; ++j) {
            if ((center - points[j]).dist() <= radius * tolerance) continue;
            center = (points[i] + points[j]) / 2;
            radius = (center - points[i]).dist();
            for (int k = 0; k < j; ++k) {
                if ((center - points[k]).dist() <= radius * tolerance) continue;
                center = ccCenter(points[i], points[j], points[k]);
                radius = (center - points[i]).dist();
            }
        }
    }
    return {center, radius};
}
