/* 
 * Usage : 
 * Returns the area of the intersection of a circle with a CCW polygon.
 * Time complexity : O(n)
*/

typedef Point<double> P;
double circlePoly(P c, double r, vector<P> ps) {
	auto angle = [](P p, P q) { return atan2(p.cross(q), p.dot(q)); };
	auto tri = [&](P p, P q) {
		auto r2 = r * r / 2;
		P d = q - p;
		auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
		auto det = a * a - b;
		if (det <= 0) return angle(p, q) * r2;
		auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
		if (t < 0 || 1 <= s) return angle(p, q) * r2;
		P u = p + d * s, v = p + d * t;
		return angle(p,u) * r2 + u.cross(v)/2 + angle(v,q) * r2;
	};
	auto sum = 0.0;
	for (int i = 0; i < (int)ps.size(); ++i)
		sum += tri(ps[i] - c, ps[(i + 1) % ps.size()] - c);
	return sum;
}
