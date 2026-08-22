
typedef Point<double> P;

struct Circle {
    P center;
    double radius;
    Circle(P c, double r) : center(c), radius(r) {}
};

// Function to calculate the Euclidean distance between two points
double distance(const P& p1, const P& p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

// Check if a point is inside a given circle
bool isPointInsideCircle(const P& p, const Circle& c) {
    return distance(p, c.center) <= c.radius;
}

// Create a circle from two points
Circle circleFromTwoPoints(const P& p1, const P& p2) {
    P center((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
    double radius = distance(p1, p2) / 2.0;
    return Circle(center, radius);
}

// Create a circle from three points using the circumcircle formula
Circle circleFromThreePoints(const P& p1, const P& p2, const P& p3) {
    double ax = p1.x, ay = p1.y;
    double bx = p2.x, by = p2.y;
    double cx = p3.x, cy = p3.y;

    double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    if (d == 0) throw runtime_error("Collinear points");

    double ux = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) + (cx * cx + cy * cy) * (ay - by)) / d;
    double uy = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) + (cx * cx + cy * cy) * (bx - ax)) / d;

    P center(ux, uy);
    double radius = distance(center, p1);
    return Circle(center, radius);
}

// Welzl's algorithm to find the minimum enclosing circle
Circle welzlAlgorithm(vector<P>& points, vector<P> boundary = {}) {
    if (points.empty() || boundary.size() == 3) {
        if (boundary.empty()) return Circle(P(0, 0), 0);
        if (boundary.size() == 1) return Circle(boundary[0], 0);
        if (boundary.size() == 2) return circleFromTwoPoints(boundary[0], boundary[1]);
        return circleFromThreePoints(boundary[0], boundary[1], boundary[2]);
    }

    P p = points.back();
    points.pop_back();

    Circle d = welzlAlgorithm(points, boundary);

    if (isPointInsideCircle(p, d)) {
        points.push_back(p);
        return d;
    }

    boundary.push_back(p);
    Circle result = welzlAlgorithm(points, boundary);
    points.push_back(p);
    return result;
}

Circle findMinimumEnclosingCircle(vector<P>& points) {
    srand(time(0));
    random_shuffle(points.begin(), points.end());
    return welzlAlgorithm(points);
}
