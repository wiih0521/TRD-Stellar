/* 
 * Usage :
 * Finds the intersection between a circle and a line.
 * Returns a vector of either 0, 1, or 2 intersection points.
 * P is intended to be Point<double>.
 */

template<class Point>
vector<Point> circleLine(Point c, double r, Point a, Point b) {
	Point ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	Point h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}